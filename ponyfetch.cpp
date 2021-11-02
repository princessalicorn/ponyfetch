#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstdlib>

#include "config.h"

using namespace std;


namespace system_information
{
    string get_info_from_env(const char* envvar)
    {
        string get_env_var;
        string ret_env_var;
        stringstream safereturn;
        get_env_var = getenv(envvar); //You could just return the char* here but that is not a good idea.
        safereturn << get_env_var;
        ret_env_var = safereturn.str();
        return ret_env_var;
    }
    string distro_name()
    {
        string buffer;
        string linev;
        ifstream distrofile;
        string delimiter = "\"";
        string output;
        unsigned int line = 0;
        string searval = "PRETTY_NAME";

        distrofile.open("/etc/os-release", ios::in);
        if(!distrofile)
        {
            cerr << "/etc/os-release does not exist. Come back here once you install your Linux distro." << endl;
        }

        while(getline(distrofile, linev)) {
            line++;
            if (linev.find(searval, 0) != string::npos) {
                break;
            }
        }
        linev.erase(0, 13);
        linev.erase(linev.size() - 1);
        distrofile.close();
        return linev;

    }
    string kernel_version()
    {
        stringstream buffer;
        ifstream versionfile;
        string delimiter = " ";
        string output;

        versionfile.open("/proc/version", ios::in);
        if(!versionfile)
        {
            cerr << "/proc/version does not exist. Is your computer on fire? Or worse... YOU USE WINDOWS." << endl;
        }
        versionfile.seekg(14, ios::beg);                              //reads to 14th byte in file
        buffer << versionfile.rdbuf();                               //Transfer rest of file to variable
        string filestring = buffer.str();                           //String Conversion
        output = filestring.substr(0, filestring.find(delimiter)); //Cut it out at the next space
        versionfile.close();                                      //Be a good mare and close out the file
        return output;                                           //And done!
    }
    string sys_uptime()
    {
        int time;
        int hours;
        int hremainder;
        int minutes;
        int seconds;
        stringstream buffer;
        ifstream uptimefile;
        string delimiter = ".";
        string output;
        string result;

        uptimefile.open("/proc/uptime", ios::in);
        if(!uptimefile)
        {
            cerr << "/proc/uptime does not exist. Are you in a time machine?" << endl;
        }
        buffer << uptimefile.rdbuf();                                //Transfer rest of file to variable
        string filestring = buffer.str();                           //String Conversion
        output = filestring.substr(0, filestring.find(delimiter)); //Cut it out at the decimal because no floats.
        uptimefile.close();                                       //Be a good mare and close out the file
        time = stoi(output);                                     //String to int
        hours = (int)time / 3600;                               //3600 seconds in an hour
        hremainder = time % 3600;                              //Getting minutes and seconds
        minutes = (int)hremainder / 60;                       //The rest is self-explanatory
        seconds = hremainder % 60;

        stringstream outputstr;
        outputstr << hours << " hours " << minutes << " minutes " << seconds << " seconds ";
        result = outputstr.str();

        return result;  //And done!
    }

};

void generate_ponyfetch_prompt()
{
    cout << "         ,--, " << "Distro: " << system_information::distro_name() << "\n";
    cout << "  _ ___/ /\\|  " << "Kernel: " << system_information::kernel_version() << "\n";
    cout << " ;( )__, )    "  << "Shell: " << system_information::get_info_from_env("SHELL") << "\n";
    cout << "; //   \'--;   " << "Uptime: " << system_information::sys_uptime() << "\n";
    cout << "  \\     |     " << "Desktop: " << system_information::get_info_from_env("DESKTOP_SESSION") << "\n";
    cout << "   ^    ^     " << "Terminal: " << system_information::get_info_from_env("TERM") << "\n";
}

int main()
{
    generate_ponyfetch_prompt();
    //system_information::distro_name();
    return 0;
}
