/*
 * This file is a part of the TChecker project.
 *
 * See files AUTHORS and LICENSE for copyright details.
 *
 */

#ifndef TCHECKER_SYNCPROD_SYSTEM_HH
#define TCHECKER_SYNCPROD_SYSTEM_HH

#include <string>
#include <vector>

#include "tchecker/parsing/declaration.hh"
#include "tchecker/system/edge.hh"
#include "tchecker/system/system.hh"
#include "tchecker/utils/iterator.hh"

/*!
 \file system.hh
 \brief System of processes for synchronized product of processes
 */

namespace tchecker {
  
  namespace syncprod {
    
    /*!
     \class system_t
     \brief System of processes
     */
    class system_t : private tchecker::system::system_t {
      /*!
       \brief Type of collection of asynchronous edges
       */
      using asynchronous_edges_collection_t = std::vector<tchecker::system::edge_const_shared_ptr_t>;
    public:
      /*!
       \brief Constructor
       \param sysdecl : system declaration
       */
      system_t(tchecker::parsing::system_declaration_t const & sysdecl);
      
      /*!
       \brief Constructor
       \param system : system of timed processes
       \post this is a copy of system
       */
      system_t(tchecker::system::system_t const & system);
      
      /*!
       \brief Copy constructor
       */
      system_t(tchecker::syncprod::system_t const &) = default;
      
      /*!
       \brief Move constructor
       */
      system_t(tchecker::syncprod::system_t &&) = default;
      
      /*!
       \brief Destructor
       */
      ~system_t() = default;
      
      /*!
       \brief Assignment operator
       */
      tchecker::syncprod::system_t & operator= (tchecker::syncprod::system_t const &) = default;
      
      /*!
       \brief Move-assignment operator
       */
      tchecker::syncprod::system_t & operator= (tchecker::syncprod::system_t &&) = default;
      
      
      // System
      using tchecker::system::system_t::name;
      using tchecker::system::system_t::attributes;
      
      // Clocks
      using tchecker::system::system_t::clocks_count;
      using tchecker::system::system_t::clock_id;
      using tchecker::system::system_t::clock_name;
      using tchecker::system::system_t::clock_attributes;
      using tchecker::system::system_t::clock_variables;
      using tchecker::system::system_t::is_clock;
      
      // Edges
      using tchecker::system::system_t::edges_count;
      using tchecker::system::system_t::edge;
      using tchecker::system::system_t::edges;
      using tchecker::system::system_t::outgoing_edges;
      using tchecker::system::system_t::incoming_edges;
      using tchecker::system::system_t::outgoing_event;
      using tchecker::system::system_t::incoming_event;
      using tchecker::system::system_t::outgoing_edges_maps;
      using tchecker::system::system_t::incoming_edges_maps;
      using tchecker::system::system_t::is_edge;
      
      /*!
       \brief Asynchronous edge check
       \param edge : an edge
       \return true if edge is asynchronous in this system, false otherwise
       */
      bool is_asynchronous(tchecker::system::edge_t const & edge) const;
      
      /*!
       \brief Type of iterator over asynchronous const edges
       */
      class asynchronous_edges_const_iterator_t : public asynchronous_edges_collection_t::const_iterator {
      public:
        /*!
         \brief Default constructor
         */
        asynchronous_edges_const_iterator_t() = default;
        
        /*!
         \brief Constructor
         \param it : iterator over collection of asynchronous edges
         */
        asynchronous_edges_const_iterator_t(asynchronous_edges_collection_t::const_iterator const & it);
        
        /*!
         \brief Dereference operator
         \return current asynchronous edge, viewed as a constant edge
         */
        tchecker::system::edge_const_shared_ptr_t operator* () const;
      };
      
      /*!
       \brief Accessor
       \param loc : location identifier
       \return range of outgoing asynchronous edges from loc
       */
      tchecker::range_t<asynchronous_edges_const_iterator_t>
      asynchronous_outgoing_edges(tchecker::loc_id_t loc) const;
      
      /*!
       \brief Accessor
       \param loc : location identifier
       \return range of incoming asynchronous edges from loc
       */
      tchecker::range_t<asynchronous_edges_const_iterator_t>
      asynchronous_incoming_edges(tchecker::loc_id_t loc) const;
      
      
      // Events
      using tchecker::system::system_t::events_count;
      using tchecker::system::system_t::event_id;
      using tchecker::system::system_t::event_name;
      using tchecker::system::system_t::event_attributes;
      using tchecker::system::system_t::is_event;
      
      // Bounded integer variables
      using tchecker::system::system_t::intvars_count;
      using tchecker::system::system_t::intvar_id;
      using tchecker::system::system_t::intvar_name;
      using tchecker::system::system_t::intvar_attributes;
      using tchecker::system::system_t::integer_variables;
      using tchecker::system::system_t::is_intvar;
      
      // Locations
      using tchecker::system::system_t::locations_count;
      using tchecker::system::system_t::location;
      using tchecker::system::system_t::locations;
      using tchecker::system::system_t::initial_locations;
      using tchecker::system::system_t::is_location;
      
      // Processes
      using tchecker::system::system_t::processes_count;
      using tchecker::system::system_t::process_id;
      using tchecker::system::system_t::process_name;
      using tchecker::system::system_t::process_attributes;
      using tchecker::system::system_t::is_process;
      
      // Synchronizations
      using tchecker::system::system_t::synchronizations_count;
      using tchecker::system::system_t::synchronization;
      using tchecker::system::system_t::synchronizations;
      
      // Cast
      
      /*!
       \brief Cast
       \return this as a tchecker::system::system_t instance
       */
      constexpr inline tchecker::system::system_t const & as_system_system() const
      {
        return *this;
      }
    private:
      // Hidden modifiers
      using tchecker::system::system_t::add_clock;
      using tchecker::system::system_t::add_edge;
      using tchecker::system::system_t::add_event;
      using tchecker::system::system_t::add_intvar;
      using tchecker::system::system_t::add_location;
      using tchecker::system::system_t::add_process;
      using tchecker::system::system_t::add_synchronization;
      
      /*!
       \brief Extract asynchronous edges
       \post all asynchronous edges from underlying system have been added to the maps
       */
      void extract_asynchronous_edges();
      
      /*!
       \brief Add asynchronous edge
       \param edge : an edge
       \pre edge is asynchronous (checked by assertion)
       \post edge has been added to the collection of outgoing asynchronous edges of its source location,
       and to the collection of incoming asynchronous edges of its target location
       */
      void add_asynchronous_edge(tchecker::system::edge_const_shared_ptr_t const & edge);
      
      std::vector<asynchronous_edges_collection_t> _async_outgoing_edges; /*!< Map : loc id -> asynchronous outgoing edges */
      std::vector<asynchronous_edges_collection_t> _async_incoming_edges; /*!< Map : loc id -> asynchronous incoming edges */
      static asynchronous_edges_collection_t const _empty_async_edges;    /*!< Empty collection of asynchronous edges */
    };
    
    
    
    
    /*!
     \brief Computes the synchronized product of a system of timed processes
     \param system : a system
     \param process_name : resulting process name
     \param separator : a separator string
     \returns a system that corresponds to the synchronized product of timed processes in system
     \post the names of locations and events in the returned system are made from tuple of locations and edges in system,
     separated by separator
     */
    tchecker::system::system_t synchronized_product(tchecker::syncprod::system_t const & system,
                                                    std::string const & process_name,
                                                    std::string const & separator);
    
  } // end of namespace syncprod
  
} // end of namespace tchecker

#endif // TCHECKER_SYNCPROD_SYSTEM_HH
