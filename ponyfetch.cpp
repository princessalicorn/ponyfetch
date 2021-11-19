#include "config.hpp"

#include <cstdio>
#include <string.h>
#include <utmpx.h>
#include <sys/systeminfo.h>

#ifdef __linux
#define OS_TYPE 0
#endif

#ifdef __sun
#define OS_TYPE 1
#endif

using namespace std;

namespace system_information
{
    string get_info_from_env(const char* envvar)
    {
        const char* get_env_var = getenv(envvar);
        string ret_env_var;
        stringstream safereturn;
        if (get_env_var != NULL)
        {
                safereturn << get_env_var;
                ret_env_var = safereturn.str();
        } else
        {
                ret_env_var = "None";
        }
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

        if (OS_TYPE == 0)
        {
                distrofile.open("/etc/os-release", ios::in);
                if(!distrofile)
                {
                cerr << "/etc/os-release does not exist. Come back here once you install your Linux distro." << endl;
                }

                while(getline(distrofile, linev))
                {
                        line++;
                        if (linev.find(searval, 0) != string::npos)
                        {
                                break;
                        }
                }

                linev.erase(0, 13);
                linev.erase(linev.size() - 1);
        }
        if (OS_TYPE == 1)
        {
                ifstream distrofile("/etc/release");
                if (distrofile.good())
                {
                        distrofile >> ws;
                        getline(distrofile, linev);
                } else
                {
                        cerr << "/etc/release does not exist." << endl;
                }
        }
        distrofile.close();
        return linev;

    }
    string kernel_version()
    {
        stringstream buffer;
        ifstream versionfile;
        string delimiter = " ";
        string output;
        if (OS_TYPE == 0)
        {
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
        }
        if (OS_TYPE == 1)
        {
                char out[16];
                sysinfo(SI_RELEASE, out, sizeof(out)/sizeof(*out));
                string retval(out);
                output = retval;
        }
        return output;                                           //And done!
    }
    string sys_uptime()
    {
        int divtime;
        int hours;
        int hremainder;
        int minutes;
        int seconds;
        stringstream buffer;
        ifstream uptimefile;
        string delimiter = ".";
        string output;
        string result;

        if (OS_TYPE == 0)
        {
                uptimefile.open("/proc/uptime", ios::in);
                if(!uptimefile)
                {
                        cerr << "/proc/uptime does not exist. Are you in a time machine?" << endl;
                }
                buffer << uptimefile.rdbuf();                                //Transfer rest of file to variable
                string filestring = buffer.str();                           //String Conversion
                output = filestring.substr(0, filestring.find(delimiter)); //Cut it out at the decimal because no floats.
                uptimefile.close();                                       //Be a good mare and close out the file
                divtime = stoi(output);                                  //String to int
        }
        if (OS_TYPE == 1)
        {
                int boottime = 0; //Taken from http://xaxxon.slackworks.com/rsapi/
                int currenttime = time(NULL);
                struct utmpx * ent;
                while((ent = getutxent()))
                {
                        if (!strcmp ("system boot", ent->ut_line))
                        {
                                boottime = ent->ut_tv.tv_sec;
                        }
                }
                divtime = currenttime - boottime;

        }
        hours = (int)divtime / 3600;                               //3600 seconds in an hour
        hremainder = divtime % 3600;                              //Getting minutes and seconds
        minutes = (int)hremainder / 60;                          //The rest is self-explanatory
        seconds = hremainder % 60;

        stringstream outputstr;
        outputstr << hours << " hours " << minutes << " minutes " << seconds << " seconds ";
        result = outputstr.str();

        return result;  //And done!
    }

};

void generate_ponyfetch_prompt()
{
    cout << ascii_lines::line1 << labels::label1 << system_information::distro_name() << "\n";
    cout << ascii_lines::line2 << labels::label2 << system_information::kernel_version() << "\n";
    cout << ascii_lines::line3 << labels::label3 << system_information::get_info_from_env("SHELL") << "\n";
    cout << ascii_lines::line4 << labels::label4 << system_information::sys_uptime() << "\n";
    cout << ascii_lines::line5 << labels::label5 << system_information::get_info_from_env("DESKTOP_SESSION") << "\n";
    cout << ascii_lines::line6 << labels::label6 << system_information::get_info_from_env("TERM") << "\n";
}

int main()
{
    generate_ponyfetch_prompt();
    //system_information::distro_name();
    return 0;
}
