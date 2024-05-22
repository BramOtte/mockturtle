#pragma once

#include <alice/alice.hpp>

#include <mockturtle/algorithms/aig_balancing.hpp>
#include <mockturtle/algorithms/rewrite.hpp>
#include <mockturtle/networks/aig.hpp>
#include <mockturtle/utils/tech_library.hpp>
#include <mockturtle/views/names_view.hpp>
#include "../../store/network_manager.hpp"


namespace alice
{

/* Writes a network to file */
class balance_command : public alice::command
{
public:
  explicit balance_command( const environment::ptr& env )
      : command( env,
                 "Performs technology-independent rewriting of the logic network." )
  {
    /* TODO: add flags */
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

      aig_balance(aig, ps);
    }
  }

  private:
    mockturtle::aig_balancing_params ps;
};

ALICE_ADD_COMMAND( balance, "Synthesis" );

} // namespace alice