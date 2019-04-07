//Babiienko, K-11
#ifndef INTERFACE1_H_INCLUDED
#define INTERFACE1_H_INCLUDED
#include <string>

class Greenhouse;
void do_comm_on(std::string &comm, Greenhouse& greenhouse);
void do_comm_of(std::string &comm, Greenhouse& greenhouse);
void win_op_err_check(Greenhouse& greenhouse);
void win_cl_err_check(Greenhouse& greenhouse);
void heat_on_err_check(Greenhouse& greenhouse);
void heat_of_err_check(Greenhouse& greenhouse);
void instruct();
void run_app();

#endif // INTERFACE1_H_INCLUDED
