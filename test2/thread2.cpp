#include <stdio.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <algorithm>
#include <time.h>
#include <condition_variable>
#include <assert.h>

#define MAX_DPT 10000
#define DEFAULT_DPT 5000
using namespace std;
template<typename T>
class FIFO
{
    public:
    FIFO(int _depth)
    {
        if(_depth<=0 || _depth>=MAX_DPT)
            depth = DEFAULT_DPT;
        depth = _depth;
        item = new T[depth];
        index = 0;
    }
    FIFO()
    {
        depth = DEFAULT_DPT;
        item = new T[depth];
        index = 0;
    }
    ~FIFO()
    { 
        delete[] item;
    }

    T Pop()
    {
        std::string _item;

        std::unique_lock<std::mutex> lock (mtx);  
        while(index == 0)
            cv.wait(lock); 
        assert(index != 0);
        _item = item[index-1];
        index--;
        if(index==(depth-1))
            cv.notify_all();
        //cout<<"pop ,nr "<<index<<endl;
        return _item;
    }

    void Push(T &_item)
    {
        std::unique_lock<std::mutex> lock (mtx);
        while(index == depth)
            cv.wait(lock);
        assert(index != depth);
        item[index] = _item;
        index++;

        cv.notify_all();
        //cout<<"push ,nr "<<index<<endl;
    }

    int size()
    {
        std::unique_lock<std::mutex> lock (mtx);
        return index;
    }

    private:
        T *item;
        int depth,index;
        std::mutex mtx;
        std::condition_variable cv;
};

std::string randomstr(int count)
{
    std::string result = "";
    for(int i=0;i<count;++i)
    {
        switch((rand()%3))
        {
            case 0:
                result += ('0'+rand()%10);
                break;
            case 1:
                result += ('A'+rand()%26);
                break;
            case 2:
                result += ('a'+rand()%26);
                break;
            default:
                break;
        }
    }
    return result;
}
/*
void sort(std::string &str)
{
    int i,j,len=str.length();
    char *p = str.c_str();
    for(i=0;i<len;i++)
        for(j=i;j<len;j++)
        {}
}*/
void product(FIFO<std::string> &fifo)
{  
    std::string str;
    long long s_cnt=0,f_cnt=0;
    while(1)
    {
        str = randomstr(12);
        fifo.Push(str);
        s_cnt++;
    }
}

void customer(FIFO<std::string> &fifo)
{
    std::string str;
    long long s_cnt=0;
    time_t tm = time(NULL),now;

    while(1)
    {
        str = fifo.Pop();
        
        s_cnt++;
        //cout<<str<<endl;
        std::sort(str.begin(), str.end());
        //cout<<str<<endl;
        
        
        if(s_cnt>0 && s_cnt%200000==0)
        {
            now = time(NULL);
            cout<<(double)s_cnt/(now-tm)<<" times per seconds"<<endl;
        }
    }
}

int main()
{
    FIFO<std::string> fifo(DEFAULT_DPT);
    std::string str,str2;
    time_t tm = time(NULL),now;
    long long s_cnt=0;

    while(1)
    {
        str = randomstr(12);
        fifo.Push(str);
        str2 = fifo.Pop();
        
        s_cnt++;
        
        std::sort(str.begin(), str.end());
        
        if(s_cnt>0 && s_cnt%200000==0)
        {
            now = time(NULL);
            cout<<(double)s_cnt/(now-tm)<<" times per seconds"<<endl;
        }
    }
    return 0;
}
