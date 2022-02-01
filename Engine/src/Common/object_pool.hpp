//
//  object_pool.hpp
//  Engine
//
//  Created by krzysp on 01/02/2022.
//

#ifndef object_pool_hpp
#define object_pool_hpp

#include <iostream>

#define OBJECT_POOL_DEFAULT_COUNT 100

namespace engine
{
    template <typename T>
    class ObjectPool
    {
        std::vector<std::unique_ptr<T>> m_items;
        std::vector<T*> m_stack;
        std::vector<T*> m_used;
    public:
        /** Create a pool of objects with a default nubmer of items = 100.
            Provide a lambda to create the object.*/
        ObjectPool(std::function<T*(void)> creator)
        {
            SetupObjects(OBJECT_POOL_DEFAULT_COUNT, creator);
        }

        /** Create a pool of objects with a designated number of items */
        ObjectPool(int count, std::function<T*(void)> creator)
        {
            SetupObjects(count, creator);
        }

        /** Dequeue an object. If possible will be taken from the pool and
            returned to the caller. When done with the object it should be
            put back on the stack again.
            Returns an object or nil. */
        T* Dequeue()
        {
            if (!m_stack.empty())
            {
                auto *any = m_stack.front();
                m_used.emplace_back(any);
                return any;
            }
            else
            {
                return nullptr;
            }
        }

        /** Put back the object. Returns the item to the stack.
         */
        void PutBack(T *item)
        {
            auto it = std::find(m_used.begin(), m_used.end(), item);
            if (it != m_used.end())
            {
                m_used.erase(it);
            };
        }

    private:
        void SetupObjects(int count, std::function<T*(void)> creator)
        {
            for (int i = 0; i < count; i++)
            {
                T *item = creator();
                m_items.emplace_back(std::unique_ptr<T>(std::move(item)));
            }

            for (auto& item : m_items)
            {
                m_stack.emplace_back(item.get());
            }
        }
    };
};

#endif /* object_pool_hpp */
