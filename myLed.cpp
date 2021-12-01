// File name: myLed.cpp
// edited by Joshua Gillespie 11/30/21
// this is a CGI application
// This application allows the user to control an led 3
// This user can turn the led on, off, or blink with given amount
//


#include <iostream>         // for the input/output
#include <stdlib.h>         // for the getenv call
#include <sys/sysinfo.h>    // for the system uptime call
#include <cgicc/Cgicc.h>    // the cgicc headers
#include <cgicc/CgiDefs.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <string>
#include <unistd.h>

#define LED_GPIO "/sys/class/gpio/gpio60/"

using namespace std;
using namespace cgicc;

void writeGPIO(string filename, string value){
   fstream fs;
   string path(LED_GPIO);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}

int main(){
   Cgicc form;                      // the CGI form object
   string cmd;                      // the Set LED command
   writeGPIO("direction", "out");
   // get the state of the form that was submitted - script calls itself
   bool isStatus = form.queryCheckbox("status");
   form_iterator it = form.getElement("cmd");  // the radio command
   if (it == form.getElements().end() || it->getValue()==""){
      cmd = "off";                     // if it is invalid use "off"
   }
   else { cmd = it->getValue(); }      // otherwise use submitted value
   char *value = getenv("REMOTE_ADDR");    // The remote IP address
 
   // generate the form but use states that are set in the submitted form
   cout << HTTPHTMLHeader() << endl;       // Generate the HTML form
   cout << html() << head() << title("Homework 10 Problem 3") << head() << endl;
   cout << body() << h1("CPE 422/522 Project: Post LED Example") << endl;;
   cout << h1("Controlling a GPIO pin via a web browser") << endl;
   cout << "<form action=\"/cgi-bin/myLed.cgi\" method=\"POST\">\n";
   cout << "<div>Set LED: <input type=\"radio\" name=\"cmd\" value=\"on\""
        << ( cmd=="on" ? "checked":"") << "/> On ";
   cout << "<input type=\"radio\" name=\"cmd\" value=\"off\""
        << ( cmd=="off" ? "checked":"") << "/> Off ";
   //adding blink
   cout << "<input type=\"radio\" name=\"cmd\" value=\"blink\""
	<< ( cmd=="blink" ? "checked":"") << "/> Blink ";

   cout << "<input type=\"submit\" value=\"Set LED\" />";

   cout << "Number of Blinks: <input type=\"text\" name=\"k\" value=\"1\" />" << endl;

   cout << "</div></form>";
 
   // process the form data to change the LED state
   string form_iterator = form.getElement("k")->getValue();
   int iterator = stoi(form_iterator);
   if (cmd=="on") writeGPIO("value", "1");              // turn on
   else if (cmd=="off") writeGPIO("value", "0");        // turn off
   else if (cmd=="blink") { //blink i k times
	   for (int i = 0; i < iterator; i++) {
		   writeGPIO("value","1");
		   sleep(1);
		   writeGPIO("value","0");
		   sleep(1);
	   }
   }
   else cout << "<div> Invalid command! </div>";        // not possible
   cout << "<div> The CGI REMOTE_ADDR value is " << value << "</div>";
   cout << body() << html();
   return 0;
}
