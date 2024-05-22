#pragma once

#include <alice/alice.hpp>

#include <mockturtle/algorithms/aig_resub.hpp>
#include <mockturtle/algorithms/rewrite.hpp>
#include <mockturtle/networks/aig.hpp>
#include <mockturtle/utils/tech_library.hpp>
#include <mockturtle/views/names_view.hpp>
#include "../../store/network_manager.hpp"


namespace alice
{

/* Writes a network to file */
class aig_resub_command : public alice::command
{
public:
  explicit aig_resub_command( const environment::ptr& env )
      : command( env,
                 "Performs technology-independent rewriting of the logic network." )
  {
    opts.add_flag( "--verbose,-v", ps.verbose, "toggle verbose printout [default = no]" );
    opts.add_option("--max_inserts", ps.max_inserts, "todo");
    opts.add_option("--max_pis", ps.max_pis, "todo");
    opts.add_option("--max_divisors", ps.max_divisors, "todo");
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

      aig_resubstitution( aig, ps );
      aig = cleanup_dangling( aig );
    }
  }
private:
  mockturtle::resubstitution_params ps;

};

ALICE_ADD_COMMAND( aig_resub, "Synthesis" );

} // namespace alice