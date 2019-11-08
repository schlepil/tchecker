/*
 * This file is a part of the TChecker project.
 *
 * See files AUTHORS and LICENSE for copyright details.
 *
 */

#ifndef TCHECKER_WAITING_HH
#define TCHECKER_WAITING_HH

#include <functional>
#include <queue>
#include <stack>

/*!
 \file waiting.hh
 \brief Waiting containers
 */

namespace tchecker {
  
#ifdef HIDDEN_TO_COMPILER
  /*!
   \class waiting_t
   \brief Interface to waiting container
   \tparam T : type of waiting elements
   */
  template <class T>
  class waiting_t {
  public:
    /*!
     \brief Destructor
     */
    virtual ~waiting_t() = default;
    
    /*!
     \brief Accessor
     \return true if the container is empty, false otherwise
     */
    virtual bool empty() = 0;
    
    /*!
     \brief Insert
     \param t : element
     \post t has been inserted in this container
     */
    virtual void insert(T const & t) = 0;
    
    /*!
     \brief Remove first element
     \pre not empty()
     \post the first element has been removed
     */
    virtual void remove_first() = 0;
    
    /*!
     \brief Accessor
     \pre not empty()
     \return first element of this container
     */
    virtual T const & first() const = 0;
  };
#endif // HIDDEN_TO_COMPILER
  
  
  
  
  /*!
   \class lifo_waiting_t
   \brief Waiting container with a Last-In-First-Out policy (stack)
   \tparam T : type of waiting elements
   */
  template <class T>
  class lifo_waiting_t {
  public:
    /*!
     \brief Type of waiting element
     */
    using element_t = T;
    
    /*!
     \brief Accessor
     \return true if the container is empty, false otherwise
     */
    inline bool empty() const
    {
      return _stack.empty();
    }
    
    /*!
     \brief Insert
     \param t : element
     \post t has been inserted on top of the stack
     */
    inline void insert(T const & t)
    {
//      _stack.push(t);
      _stack.push_back(t);
    }
    
    /*!
     \brief Remove top element
     \pre not empty()
     \post top element has been removed from the stack
     */
    inline void remove_first()
    {
//      _stack.pop();
      _stack.pop_back();
    }
    
    /*!
     \brief Accessor
     \pre not empty()
     \return top element of the stack
     */
    inline T const & first() const
    {
//      return _stack.top();
      return _stack.back();
    }
  
    /*!
     * \brief Swap to limit interactions with reference counter
     * \param t : "swapable" element ( intrusive_shared )
     * \pre t holds some value
     * \post t is inserted into the stack, t holds now a "nullptr"
     * \note redundant with move-construction, but move is deleted
     */
    void swap_insert(T & t){
      //Create a new one (if T is intrusive<make_shared> this will be with a nullptr) and swap
//      _stack.emplace();
      _stack.emplace_back();
//      t.swap(_stack.top());
      t.swap(_stack.back());
    }
  
    /*!
     * \brief Swap to limit interactions with reference counter
     * \param t : "swapable" element ( intrusive_shared )
     * \pre t holds some value (usually a "nullptr")
     * \post the top value of the stack is swaped into t, the value held by t is discarded
     * \note redundant with move-construction, but move is deleted
     */
    void swap_first_and_remove(T & t){
//      t.swap(_stack.top());
      t.swap(_stack.back());
      remove_first();
    }
  
    /*!
     * Check if any is null
     */
    bool check_for_no_null(){
      for (T const & it : _stack){
        if(it == T{nullptr}){
          return false;
        };
      }
      return true;
    }
    
  private:
//    std::stack<T> _stack;  /*!< Stack of waiting elements */
    std::deque<T> _stack;  /*!< Stack of waiting elements */
  };
  
  
  
  
  /*!
   \class fifo_waiting_t
   \brief Waiting container with a First-In-First-Out policy (queue)
   \tparam T : type of waiting elements
   */
  template <class T>
  class fifo_waiting_t {
  public:
    /*!
     \brief Type of waiting element
     */
    using element_t = T;
    
    /*!
     \brief Accessor
     \return true if the container is empty, false otherwise
     */
    inline bool empty() const
    {
      return _queue.empty();
    }
    
    /*!
     \brief Insert
     \param t : element
     \post t has been inserted at the end of the queue
     */
    inline void insert(T const & t)
    {
//      _queue.push(t);
      _queue.push_back(t);
    }
    
    /*!
     \brief Remove first element
     \pre not empty()
     \post first element has been removed from the queue
     */
    inline void remove_first()
    {
//      _queue.pop();
      _queue.pop_front();
    }
    
    /*!
     \brief Accessor
     \pre not empty()
     \return first element of the queue
     */
    inline T const & first() const
    {
      return _queue.front();
    }
  
    /*!
     * Swap to limit interactions with reference counter
     */
    void swap_insert(T & t){
      //Create a new one (if T is intrusive<make_shared> this will be with a nullptr) and swap
//      _queue.emplace();
      _queue.emplace_back();
      t.swap(_queue.back());
    }
    
    /*!
     * Swap to limit interactions with reference counter
     */
    void swap_first_and_remove(T & t){
//      t.swap(_queue.back());
      t.swap(_queue.front());
      remove_first();
    }
    
    /*!
     * Check if any is null
     */
    bool check_for_no_null(){
      for (T const &it : _queue){
        if(it == T{nullptr}){
          return false;
        };
      }
      return true;
    }
    
  private:
//    std::queue<T> _queue;  /*!< Queue of waiting elements */
    std::deque<T> _queue;  /*!< Queue of waiting elements */
  };
  
  
  
  
  /*!
   \class filter_waiting_t
   \brief Waiting container with filtering
   \tparam W : type of waiting container
   \note this container extends W by filtering out elements that do not match a
   predicate. The container appears as if it only contains elements matching the
   predicate.
   */
  template <class W>
  class filter_waiting_t : public W {
  public:
    /*!
     \brief Type of waiting element
     */
    using element_t = typename W::element_t;
    
    /*!
     \brief Type of filter
     */
    using filter_t = std::function<bool(element_t const &)>;
    
    /*!
     \brief Constructor
     \param filter : a filter
     \param args : arguments to a constructor of W
     */
    template <class ... ARGS>
    filter_waiting_t(filter_t && filter, ARGS && ... args) : W(std::forward<ARGS>(args)...), _filter(filter)
    {}
    
    /*!
     \brief Copy constructor
     */
    filter_waiting_t(tchecker::filter_waiting_t<W> const &) = default;
    
    /*!
     \brief Move constructor
     */
    filter_waiting_t(tchecker::filter_waiting_t<W> &&) = default;
    
    /*!
     \brief Destructor
     */
    ~filter_waiting_t() = default;
    
    /*!
     \brief Assignment operator
     */
    tchecker::filter_waiting_t<W> & operator= (tchecker::filter_waiting_t<W> const &) = default;
    
    /*!
     \brief Move-assignment operator
     */
    tchecker::filter_waiting_t<W> & operator= (tchecker::filter_waiting_t<W> &&) = default;
    
    /*!
     \brief Accessor
     \return true if the container is empty, false otherwise
     */
    bool empty()
    {
      skip_bad();
      return W::empty();
    }
    
    /*!
     \brief Insert
     \param t : element
     \post t has been inserted in this container if t satisfies the filter
     */
    void insert(element_t const & t)
    {
      if (_filter(t))
        W::insert(t);
    }
    
    /*!
     \brief Remove first element
     \pre not empty()
     \post the first element has been removed
     */
    void remove_first()
    {
      //skip_bad();
      //assert(_filter(W::first())); // When this is called all bad should have already been removed;
      //When threading, another thread might have found a node covering this one
      if (!_filter(W::first())){
        std::cout << "Node has gone inactive" << std::endl;
      }
      assert(!empty());
      W::remove_first();
    }
    
    /*!
     \brief Accessor
     \pre not empty()
     \return first element of this container
     */
    element_t const & first()
    {
      skip_bad();
      assert(! empty());
      return W::first();
    }
    
    //swap the first element into the given to by-pass the changement of intrusive
//    void swap_first(element_t &e){
//      W::swap_first(e);
//    }
    
  private:
    /*!
     \brief Remove the bad elements in front of the waiting container
     \post If the container is not empty, then its first element satisfies _filter.
     No element satisfying _filter has been removed from the container. The ordering
     of element beyond the first element that satisfies _filter is preserved.
     */
    void skip_bad()
    {
      while ( (! W::empty()) && (! _filter(W::first())) )
        W::remove_first();
    }
    
    filter_t _filter;  /*!< Filter */
  };
  
} // end of namespace tchecker

#endif // TCHECKER_WAITING_HH
