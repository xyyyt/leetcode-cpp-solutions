#include <queue>
#include <limits>
#include <cassert>

class MedianFinder
{
public:
    void addNum(int num)
    {
        if (_leftHalf.empty())
        {
            _leftHalf.emplace(num);

            return;
        }

        if (num < _leftHalf.top())
        {
            _leftHalf.emplace(num);
        }
        else
        {
            _rightHalf.emplace(num);
        }

        int diff = _leftHalf.size() - _rightHalf.size();

        if (diff > 1)
        {
            _rightHalf.emplace(_leftHalf.top());
            _leftHalf.pop();
        }
        else if (diff < -1)
        {
            _leftHalf.emplace(_rightHalf.top());
            _rightHalf.pop();
        }
    }

    double findMedian()
    {
        if (_leftHalf.empty())
        {
            return std::numeric_limits<double>::min();
        }

        double median = 0;

        if (_leftHalf.size() == _rightHalf.size())
        {
            median = (_leftHalf.top() + _rightHalf.top()) / 2.0;
        }
        else
        {
            median = (_leftHalf.size() > _rightHalf.size()) ?
                _leftHalf.top() : _rightHalf.top();
        }

        return median;
    }

private :
    using SmallestNumsQueue_t = std::priority_queue<int>;
    using HighestNumsQueue_t = std::priority_queue<
        int, std::vector<int>, std::greater<int>>;

    SmallestNumsQueue_t _leftHalf;
    HighestNumsQueue_t _rightHalf;
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

    {
        MedianFinder medianFinder;

        medianFinder.addNum(5);
        medianFinder.addNum(10);
        assert(medianFinder.findMedian() == 7.5);
        medianFinder.addNum(1);
        assert(medianFinder.findMedian() == 5.0);
    }

    {
        MedianFinder medianFinder;

        medianFinder.addNum(100);
        assert(medianFinder.findMedian() == 100.0);
        medianFinder.addNum(200);
        assert(medianFinder.findMedian() == 150.0);
        medianFinder.addNum(300);
        assert(medianFinder.findMedian() == 200.0);
    }

    {
        MedianFinder medianFinder;

        medianFinder.addNum(-1);
        medianFinder.addNum(-2);
        assert(medianFinder.findMedian() == -1.5);
        medianFinder.addNum(-3);
        assert(medianFinder.findMedian() == -2.0);
    }

    {
        MedianFinder medianFinder;

        medianFinder.addNum(1);
        medianFinder.addNum(1);
        medianFinder.addNum(1);
        assert(medianFinder.findMedian() == 1.0);
        medianFinder.addNum(2);
        assert(medianFinder.findMedian() == 1.0);
    }

    {
        MedianFinder medianFinder;

        medianFinder.addNum(8);
        medianFinder.addNum(3);
        medianFinder.addNum(7);
        assert(medianFinder.findMedian() == 7.0);
        medianFinder.addNum(9);
        assert(medianFinder.findMedian() == 7.5);
    }

    {
        MedianFinder medianFinder;

        medianFinder.addNum(2);
        medianFinder.addNum(4);
        medianFinder.addNum(6);
        medianFinder.addNum(8);
        assert(medianFinder.findMedian() == 5.0);
        medianFinder.addNum(10);
        assert(medianFinder.findMedian() == 6.0);
    }

    {
        MedianFinder medianFinder;

        medianFinder.addNum(0);
        assert(medianFinder.findMedian() == 0.0);
        medianFinder.addNum(1000000);
        assert(medianFinder.findMedian() == 500000.0);
        medianFinder.addNum(500000);
        assert(medianFinder.findMedian() == 500000.0);
    }

    {
        MedianFinder medianFinder;

        medianFinder.addNum(9);
        medianFinder.addNum(1);
        medianFinder.addNum(4);
        medianFinder.addNum(7);
        assert(medianFinder.findMedian() == 5.5);
        medianFinder.addNum(2);
        assert(medianFinder.findMedian() == 4.0);
    }

    {
        MedianFinder medianFinder;

        medianFinder.addNum(-5);
        medianFinder.addNum(5);
        assert(medianFinder.findMedian() == 0.0);
        medianFinder.addNum(0);
        assert(medianFinder.findMedian() == 0.0);
    }

    {
        MedianFinder medianFinder;

        medianFinder.addNum(3);
        medianFinder.addNum(3);
        medianFinder.addNum(3);
        medianFinder.addNum(3);
        assert(medianFinder.findMedian() == 3.0);
    }

    return 0;
}
