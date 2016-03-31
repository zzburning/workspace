/*
固定大小的缓冲池策略
它的实现思想就是每次从List的头上取内存， 如果取不到则重新分配一定数量； 用完后把内存放回List头部，这样的话效率很高，因为每次List上可以取到的话，肯定是空闲的内存。
*/
te<typename T>
class CMemoryPool
{
    public:
        enum { EXPANSION_SIZE = 32};

        CMemoryPool(unsigned int nItemCount = EXPANSION_SIZE)
        {
            ExpandFreeList(nItemCount);
        }
        
        ~CMemoryPool()
        {
            //free all memory in the list
            CMemoryPool<T>* pNext = NULL;
            for(pNext = m_pFreeList; pNext != NULL; pNext = m_pFreeList)
            {
                m_pFreeList = m_pFreeList->m_pFreeList;
                delete [](char*)pNext;
            }
        }

        void* Alloc(unsigned int /*size*/)
        {
            if(m_pFreeList == NULL)
            {
                ExpandFreeList();
            }
            
            //get free memory from head
            CMemoryPool<T>* pHead = m_pFreeList;
            m_pFreeList = m_pFreeList->m_pFreeList;
            return pHead;
        }

        void Free(void* p)
        {
            //push the free memory back to list
            CMemoryPool<T>* pHead = static_cast<CMemoryPool<T>*>(p);
            pHead->m_pFreeList = m_pFreeList;
            m_pFreeList = pHead;
        }

    protected:
        //allocate memory and push to the list
        void ExpandFreeList(unsigned nItemCount = EXPANSION_SIZE)
        {
            unsigned int nSize = sizeof(T) > sizeof(CMemoryPool<T>*) ? sizeof(T) : sizeof(CMemoryPool<T>*);
            CMemoryPool<T>* pLastItem = static_cast<CMemoryPool<T>*>(static_cast<void*>(new char[nSize]));
            m_pFreeList = pLastItem;
            for(int i=0; i<nItemCount-1; ++i)
            {
                pLastItem->m_pFreeList = static_cast<CMemoryPool<T>*>(static_cast<void*>(new char[nSize]));
                pLastItem = pLastItem->m_pFreeList;
            }

            pLastItem->m_pFreeList = NULL;
        }

    private:
        CMemoryPool<T>* m_pFreeList;
};

class CCriticalSection
{
public:
    CCriticalSection()
    {
        InitializeCriticalSection(&m_cs);
    }

    ~CCriticalSection()
    {
        DeleteCriticalSection(&m_cs);
    }

    void Lock()
    {
        EnterCriticalSection(&m_cs); 
    }

    void Unlock()
    {
        LeaveCriticalSection(&m_cs);
    }

protected:
    CRITICAL_SECTION m_cs;
};

template<typename POOLTYPE, typename LOCKTYPE>
class CMTMemoryPool
{
    public:
        void* Alloc(unsigned int size)
        {
            void* p = NULL;
            m_lock.Lock();
            p = m_pool.Alloc(size);
            m_lock.Unlock();

            return p;
        }

        void Free(void* p)
        {
            m_lock.Lock();
            m_pool.Free(p);
            m_lock.Unlock();    
        }

    private:
        POOLTYPE m_pool;
        LOCKTYPE m_lock;
};

