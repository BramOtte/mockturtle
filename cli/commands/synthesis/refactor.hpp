#pragma once

#include <alice/alice.hpp>

#include <cstdint>
#include <iostream>
#include <mockturtle/algorithms/akers_synthesis.hpp>
#include <mockturtle/algorithms/node_resynthesis/akers.hpp>
#include <mockturtle/algorithms/node_resynthesis/sop_factoring.hpp>
#include <mockturtle/algorithms/refactoring.hpp>

#include <mockturtle/algorithms/rewrite.hpp>
#include <mockturtle/networks/aig.hpp>
#include <mockturtle/utils/tech_library.hpp>
#include <mockturtle/views/names_view.hpp>
#include "../../store/network_manager.hpp"


namespace alice
{

/* Writes a network to file */
class refactor_command : public alice::command
{
public:
  explicit refactor_command( const environment::ptr& env )
      : command( env,
                 "Performs technology-independent rewriting of the logic network." )
  {
    opts.add_flag( "--verbose,-v", ps.verbose, "toggle verbose printout [default = no]" );
    /* TODO: add other flags */
  }

protected:
  void execute()
  {
    /* TODO: check network type: currently it works only with AIGs */
    if ( store<network_manager>().empty() )
    {
      env->err() << "Empty logic network.\n";
      return;
    }
    else
    {
      using namespace mockturtle;
      
      
      network_manager::aig_names& aig = store<network_manager>().current().get_aig();
      /* TODO: make refactoring work with a sequencial network this is kinda hacky */
      names_view<aig_network> com;
      com._storage = aig._storage;

      mockturtle::sop_factoring<names_view<aig_network>> rs;
      refactoring( com, rs, ps );

      /* TODO: add other refactoring methods */


      aig = cleanup_dangling( aig );
    }
  }
private:
  mockturtle::refactoring_params ps;

};

ALICE_ADD_COMMAND( refactor, "Synthesis" );

} // namespace alice