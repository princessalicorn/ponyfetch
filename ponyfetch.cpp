#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;


namespace system_information
{
    string get_wm()
    {
        char* current_desktop;
        stringstream safedesktopreturn;
        string desktopreturn;

        current_desktop = getenv("DESKTOP_SESSION");
        safedesktopreturn << current_desktop;
        desktopreturn = safedesktopreturn.str();
        return desktopreturn;
    }
    string get_shell()
    {
        char* GetShell;
        string shell;

        GetShell = getenv("SHELL"); //You could just return the char* here but that is not a good idea.
        stringstream safeshellreturn;
        safeshellreturn << GetShell;
        shell = safeshellreturn.str();
        return shell;
    }
    string distro_name()
    {
        string buffer;
        ifstream distrofile;
        string delimiter = "\"";
        string output;

        distrofile.open("/etc/os-release", ios::in);
        if(!distrofile)
        {
            cerr << "/etc/os-release does not exist. Come back here once you install your Linux distro." << endl;
        }
        getline(distrofile, buffer);                //Grabbing OS name from the file
        buffer.erase(0, 6);                        //Erasing useless first 6 bites
        buffer.erase(buffer.size() - 1);          //Cutting off the last " from the string
        distrofile.close();                      //Be a good mare and close out the file
        return buffer;                          //Done!
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
    cout << " ;( )__, )    "  << "Shell: " << system_information::get_shell() << "\n";
    cout << "; //   \'--;   " << "Uptime: " << system_information::sys_uptime() << "\n";
    cout << "  \\     |     " << "Desktop: " << system_information::get_wm() << "\n";
    cout << "   ^    ^     " << "\n";
}

int main()
{
    generate_ponyfetch_prompt();
    return 0;
}
