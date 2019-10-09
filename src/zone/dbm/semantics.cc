/*
 * This file is a part of the TChecker project.
 *
 * See files AUTHORS and LICENSE for copyright details.
 *
 */

#include "tchecker/zone/dbm/semantics.hh"

namespace tchecker {
  
  namespace dbm {
    
    namespace details {
      
      bool constrain(tchecker::dbm::db_t * dbm,
                     tchecker::clock_id_t dim,
                     tchecker::clock_constraint_container_t const & constraints)
      {
        for (tchecker::clock_constraint_t const & c : constraints) {
          auto cmp = (c.comparator() == tchecker::clock_constraint_t::LT ? tchecker::dbm::LT : tchecker::dbm::LE);
          if (tchecker::dbm::constrain(dbm, dim, c.id1(), c.id2(), cmp, c.value()) == tchecker::dbm::EMPTY)
            return false;
        }
        return true;
      }
      
      
      void reset(tchecker::dbm::db_t * dbm, tchecker::clock_id_t dim, tchecker::clock_reset_container_t const & resets)
      {
        for (tchecker::clock_reset_t const & r : resets)
          tchecker::dbm::reset(dbm, dim, r.left_id(), r.right_id(), r.value());
      }
  
      enum tchecker::state_status_t constrain_to_reset(tchecker::dbm::db_t * dbm, tchecker::clock_id_t dim, tchecker::clock_reset_container_t const & resets)
      {
        // dbm \cap resets
        // resets of the form x=y+c become constraints of the form y+c<=x<=y+c
        // x-y <= c
        //y-x <= -c
        tchecker::dbm::status_t res;
        for (tchecker::clock_reset_t const & r : resets) {
          res = tchecker::dbm::constrain(dbm, dim, r.left_id(), r.right_id(), tchecker::dbm::LE,  r.value());
          if (!(tchecker::dbm::NON_EMPTY == res)){
            return tchecker::STATE_EMPTY_ZONE;
          }
          res = tchecker::dbm::constrain(dbm, dim, r.right_id(), r.left_id(), tchecker::dbm::LE, -r.value());
          if (!(tchecker::dbm::NON_EMPTY == res)){
            return tchecker::STATE_EMPTY_ZONE;
          }
        }
        return tchecker::STATE_OK;
      }
  
      void inverse_reset(tchecker::dbm::db_t *dbm, tchecker::clock_id_t  dim, tchecker::clock_reset_container_t const & resets)
      {
        for (tchecker::clock_reset_t const & r : resets)
          tchecker::dbm::inverse_reset(dbm, dim, r.left_id(), r.right_id(), r.value());
        return;
      }
      
      
    } // end of namespace details
    
  } // end of namespace dbm
  
} // end of namespace tchecker
