/* mockturtle: C++ logic network library
 * Copyright (C) 2018-2024  EPFL
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*!
  \file rewrite.hpp
  \brief Rewrite command

  \author Alessandro tempia Calvino
*/

#pragma once

#include <alice/alice.hpp>

#include <cstdint>
#include <iostream>
#include <mockturtle/algorithms/sim_resub.hpp>
#include <mockturtle/algorithms/rewrite.hpp>
#include <mockturtle/networks/aig.hpp>
#include <mockturtle/utils/tech_library.hpp>
#include <mockturtle/views/names_view.hpp>
#include "../../store/network_manager.hpp"


namespace alice
{

/* Writes a network to file */
class sim_resub_command : public alice::command
{
public:
  explicit sim_resub_command( const environment::ptr& env )
      : command( env,
                 "Performs technology-independent rewriting of the logic network." )
  {
    opts.add_flag( "--verbose,-v", ps.verbose, "toggle verbose printout [default = no]" );
    opts.add_option("--max_inserts", ps.max_inserts, "todo");
    opts.add_option("--max_pis", ps.max_pis, "todo");
    opts.add_option("--max_divisors", ps.max_divisors, "todo");

    // add_flag( "--zero,-z", "Performs zero-gain rewriting [default = no]" );
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

      std::cout << "max_inserts: " << ps.max_inserts << ", max_pis: " << ps.max_pis << ", max_divisors: " <<ps.max_divisors << "\n";

      
      network_manager::aig_names& aig = store<network_manager>().current().get_aig();
      names_view<aig_network> com;
      com._storage = aig._storage;

      sim_resubstitution( com, ps );
      aig = cleanup_dangling( aig );
    }
  }
private:
  mockturtle::resubstitution_params ps;

};

ALICE_ADD_COMMAND( sim_resub, "Synthesis" );

} // namespace alice