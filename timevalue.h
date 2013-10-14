/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: John Abraham <john.abraham@gatech.edu>
 */

#ifndef TIMEVALUE_H
#define TIMEVALUE_H


#include <map>
#include <ostream>
#include <sstream>
#include <QtGlobal>


template <class T>
class TimeValue {
public:
  TimeValue();
  TimeValue(const TimeValue & other);
  TimeValue <T> & operator=(const TimeValue <T> & rhs);
  typedef std::multimap<qreal, T> TimeValue_t;
  typedef std::pair<qreal, T> TimeValuePair_t;
  typedef std::pair<typename TimeValue_t::const_iterator, typename TimeValue_t::const_iterator> TimeValueIteratorPair_t;
  typedef enum {
    GOOD,
    UNDERRUN,
    OVERRUN
  } TimeValueResult_t;

  void add(qreal t, T value);
  void systemReset();
  TimeValueResult_t setCurrentTime(qreal t);
  T getCurrent();
  TimeValueIteratorPair_t getRange(qreal lowerBound, qreal upperBound);
  std::ostringstream toString();
  void setLookBack (qreal lookBack);
  bool isEnd ();

private:
  TimeValue_t m_timeValues;
  typename TimeValue<T>::TimeValue_t::const_iterator m_currentIterator;
  qreal m_lookBack;
  void rewindCurrentIterator();
};

template <class T>
TimeValue<T>::TimeValue(): m_lookBack(0)
{

}

template <class T>
TimeValue<T>::TimeValue(const TimeValue & other)
{
    for(typename TimeValue<T>::TimeValue_t::const_iterator i = other.m_timeValues.begin();
        i != other.m_timeValues.end();
        ++i)
    {
        m_timeValues[i->first] = i->second;
    }
    if(!m_timeValues.empty())
    {
        m_currentIterator = m_timeValues.begin();
    }
}


template <class T>
TimeValue <T> &
TimeValue<T>::operator= (const TimeValue <T> & other)
{
    for(typename TimeValue<T>::TimeValue_t::const_iterator i = other.m_timeValues.begin();
        i != other.m_timeValues.end();
        ++i)
    {
        m_timeValues[i->first] = i->second;
    }
    if(!m_timeValues.empty())
    {
        m_currentIterator = m_timeValues.begin();
    }
    return *this;
}

template <class T>
void
TimeValue<T>::rewindCurrentIterator()
{
    m_currentIterator = m_timeValues.begin ();
}

template <class T>
void
TimeValue<T>::add(qreal t, T value)
{
    bool wasEmpty = m_timeValues.empty();
    m_timeValues.insert(TimeValuePair_t (t, value));
    if (wasEmpty)
    {
        m_currentIterator = m_timeValues.begin();
    }
}


template <class T>
bool
TimeValue<T>::isEnd()
{
  return m_currentIterator == m_timeValues.end();
}


template <class T>
void
TimeValue<T>::systemReset()
{
    m_timeValues.clear();
}

template <class T>
typename TimeValue<T>::TimeValueIteratorPair_t
TimeValue<T>::getRange(qreal lowerBound, qreal upperBound)
{
  setCurrentTime(lowerBound);
  typename TimeValue_t::const_iterator lowerIterator = m_currentIterator;
  typename TimeValue_t::const_iterator tempIterator = m_currentIterator;
  while (tempIterator != m_timeValues.end())
    {
      if (tempIterator->first > upperBound)
        {
          --tempIterator;
          break;
        }
      ++tempIterator;
    }
  TimeValueIteratorPair_t pp (lowerIterator, tempIterator);
  return pp;
}

template <class T>
T
TimeValue<T>::getCurrent()
{
    if (m_currentIterator == m_timeValues.end())
    {
        return T(m_timeValues.rbegin()->second);
    }
    return m_currentIterator->second;
}



template <class T>
void
TimeValue<T>::setLookBack(qreal lookBack)
{
  m_lookBack = lookBack;
}

template <class T>
typename TimeValue<T>::TimeValueResult_t
TimeValue<T>::setCurrentTime(qreal t)
{
  if (m_timeValues.empty())
    {
      return UNDERRUN;
    }

  t = t - m_lookBack;
  t = qMax (t, 0.0);
  if ((!t) || (t < m_currentIterator->first))
    {
        rewindCurrentIterator();
        if (t < m_currentIterator->first)
          {
            return UNDERRUN;
          }
        return GOOD;
    }

  for(typename TimeValue<T>::TimeValue_t::const_iterator i = m_currentIterator;
        i != m_timeValues.end();
        ++i)
    {
      logQString (QString ("i->first:") + QString::number( i->first) + " t:" + QString::number(t));
        if (i->first > t)
        {
            --m_currentIterator;
            return GOOD;
        }
        else if (i->first == t)
        {
            return GOOD;
        }
        else
        {
            ++m_currentIterator;
        }
    }
    return OVERRUN;

}
template <class T>
std::ostringstream
TimeValue<T>::toString()
{
    std::ostringstream os;
    for(typename TimeValue<T>::TimeValue_t::const_iterator i = m_timeValues.begin();
        i != m_timeValues.end();
        )
    {

        std::pair<typename TimeValue_t::const_iterator, typename TimeValue_t::const_iterator> pp =  m_timeValues.equal_range(i->first);
        for(typename TimeValue<T>::TimeValue_t::const_iterator j = pp.first;
            j != pp.second;
            ++j)
        {
            os << j->second;
        }
        i = m_timeValues.upper_bound(i->first);
    }
    return os;
}

#endif // TIMEVALUE_H
