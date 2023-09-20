#ifndef _CONTAINER_H_
#define _CONTAINER_H_

template<typename T>
class Container 
{
    public:
        Container():data_(new T[1]),  size_(0), capacity_(1){}
        ~Container()
        {
            delete data_;
        }

        void operator= ( const Container& ) = delete;

        bool   IsEmpty () const {return size_ == 0;}
        size_t GetSize () const {return size_;};

        void PushBack (const T &value)
        {
            if (size_ >= capacity_) 
                this->AddMemory();
            
            data_[size_++] = value;
            return;
        }

        void PopBack  ()
        {
            if (size_ != 0) size_--;

            return;
        }

        T& operator[](size_t index) const
        {
            if (index < size_)
                return data_[index];
        }

        const T& operator[](size_t index)
        {
            if (index < size_)
                return data_[index];
        }
        
    private:

        void AddMemory ()
        {
            capacity_ *= 2;

            T* tmp = data_;
            data_ = new T[capacity_];

            for (size_t it = 0; it < size_; ++it) 
                data_[it] = tmp[it];

            delete[] tmp;
        }

        T* data_;

        size_t size_;
        size_t capacity_;
};



#endif