/*
 * This file is a part of the TChecker project.
 *
 * See files AUTHORS and LICENSE for copyright details.
 *
 */

#ifndef TCHECKER_ALGORITHMS_COVREACH_STATS_HH
#define TCHECKER_ALGORITHMS_COVREACH_STATS_HH

#include <iostream>
#include <vector>

/*!
 \file stats.hh
 \brief Statistics for covering reachability algorithm
 */

namespace tchecker {
  
  namespace covreach {
    
    /*!
     \class stats_t
     \brief Statistics for covering reachability algorithm
     */
    class stats_t {
    public:
      /*!
       \brief Constructor
       */
      stats_t();
      
      stats_t(unsigned long visited, unsigned long covered_leaves, unsigned long covered_nonleaves, unsigned long direcly_covered):
        _visited_nodes(visited),
        _covered_leaf_nodes(covered_leaves),
        _covered_nonleaf_nodes(covered_nonleaves),
        _directly_covered_leaf_nodes(direcly_covered)
      {}
      
      stats_t(const std::vector<tchecker::covreach::stats_t> & stats_vec){
        _visited_nodes=0;
        _covered_leaf_nodes=0;
        _covered_nonleaf_nodes=0;
        _directly_covered_leaf_nodes=0;
        for (const tchecker::covreach::stats_t & it : stats_vec){
          _visited_nodes += it.visited_nodes();
          _directly_covered_leaf_nodes += it.directly_covered_leaf_nodes();
          _covered_leaf_nodes += it.covered_leaf_nodes();
          _covered_nonleaf_nodes += it.covered_nonleaf_nodes();
        }
      }
      
      /*!
       \brief Copy constructor
       */
      stats_t(tchecker::covreach::stats_t const &);
      
      /*!
       \brief Move constructor
       */
      stats_t(tchecker::covreach::stats_t &&);
      
      /*!
       \brief Destructor
       */
      ~stats_t();
      
      /*!
       \brief Assignment operator
       */
      tchecker::covreach::stats_t & operator= (tchecker::covreach::stats_t const &);
      
      /*!
       \brief Move-assignment operator
       */
      tchecker::covreach::stats_t & operator= (tchecker::covreach::stats_t &&);
      
      /*!
       \brief Accessor
       \return the number of visited nodes
       */
      unsigned long visited_nodes() const;
      
      /*!
       \brief Accessor
       \return the numer of covered leaf nodes
       */
      unsigned long covered_leaf_nodes() const;
  
      /*!
       \brief Accessor
       \return the numer of covered leaf nodes
       */
      unsigned long directly_covered_leaf_nodes() const;
      
      /*!
       \brief Accessor
       \return the number of covered non-leaf nodes
       */
      unsigned long covered_nonleaf_nodes() const;
      
      /*!
       \brief Increment counter of visited nodes
       \post the number of visited nodes has increased by 1
       */
      void increment_visited_nodes();
      
      /*!
       \brief Increment counter of covered leaf nodes
       \post the number of covered leaf nodes has increased by 1
       */
      void increment_covered_leaf_nodes();
      
      /*!
       \brief Increment counter of covered non-leaf nodes
       \post the number of covered non-leaf nodes has increased by 1
       */
      void increment_covered_nonleaf_nodes();
  
      /*!
       \brief Increment counter of covered leaf nodes within the same successors
       \post the number of covered non-leaf nodes has increased by 1
       */
      void increment_directly_covered_leaf_nodes();
      
    protected:
      unsigned long _visited_nodes;          /*!< Number of visited nodes */
      unsigned long _covered_leaf_nodes;     /*!< Number of covered leaf nodes */
      unsigned long _covered_nonleaf_nodes;  /*!< Number of covered non-leaf nodes */
      unsigned long _directly_covered_leaf_nodes; /*< Number of covered leaf nodes covered by other nodes in the current successors */
    };
    
    
    
    
    /*!
     \brief Output operator for stats
     \param os : output stream
     \param s : stats
     \post s has been output to os
     \return os after output
     */
    std::ostream & operator<< (std::ostream & os, tchecker::covreach::stats_t const & stats);
    
  } // end of namespace covereach
  
} // end of namespace tchecker

#endif // TCHECKER_ALGORITHMS_COVREACH_STATS_HH
