#include <queue>
#include <limits>
#include <cassert>

class MedianFinder
{
public:
    void addNum(int num)
    {
        if (_queue.empty())
        {
            _queue.emplace(num);

            return;
        }

        if (num < _queue.top())
        {
            _queue.emplace(num);
        }
        else
        {
            _queue2.emplace(num);
        }

        int diff = _queue.size() - _queue2.size();

        if (diff > 1)
        {
            _queue2.emplace(_queue.top());
            _queue.pop();
        }
        else if (diff < -1)
        {
            _queue.emplace(_queue2.top());
            _queue2.pop();
        }
    }

    double findMedian()
    {
        if (_queue.empty())
        {
            return std::numeric_limits<double>::min();
        }

        double median = 0;

        if (_queue.size() == _queue2.size())
        {
            median = (_queue.top() + _queue2.top()) / 2.0;
        }
        else
        {
            median = (_queue.size() > _queue2.size()) ?
                _queue.top() : _queue2.top();
        }

        return median;
    }

private :
    using SmallestNumsQueue_t = std::priority_queue<int>;
    using HighestNumsQueue_t = std::priority_queue<
        int, std::vector<int>, std::greater<int>>;

    SmallestNumsQueue_t _queue;
    HighestNumsQueue_t _queue2;
};

int main()
{
    {
        MedianFinder medianFinder;

        medianFinder.addNum(1);
        medianFinder.addNum(2);
        assert(medianFinder.findMedian() == 1.5);
        medianFinder.addNum(3);
        assert(medianFinder.findMedian() == 2.0);
    }

    {
        MedianFinder medianFinder;

        medianFinder.addNum(5);
        assert(medianFinder.findMedian() == 5.0);
        medianFinder.addNum(15);
        assert(medianFinder.findMedian() == 10.0);
        medianFinder.addNum(1);
        assert(medianFinder.findMedian() == 5.0);
        medianFinder.addNum(3);
        assert(medianFinder.findMedian() == 4.0);
        medianFinder.addNum(2);
        assert(medianFinder.findMedian() == 3.0);
        medianFinder.addNum(8);
        assert(medianFinder.findMedian() == 4.0);
    }

    {
        MedianFinder medianFinder;

        medianFinder.addNum(2);
        assert(medianFinder.findMedian() == 2.0);
        medianFinder.addNum(2);
        assert(medianFinder.findMedian() == 2.0);
        medianFinder.addNum(2);
        assert(medianFinder.findMedian() == 2.0);
        medianFinder.addNum(2);
        assert(medianFinder.findMedian() == 2.0);
    }

    return 0;
}
