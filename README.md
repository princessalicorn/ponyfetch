# ponyfetch
## Simple Fetch Software for POSIX operating systems
### Current Version: 1.4.1

### Whats new in 1.4.1?
  - Ponyfetch compatibility with FreeBSD!
  - Ensured Clang++ compatibility

Have you ever wanted ponies to corrode your fetch software, no? Too bad!

![ponyfetch](https://github.com/ameliaprogs/ponyfetch/blob/main/ponyfetch.png?raw=true)

(ASCII Sauce: https://www.asciiart.eu/animals/horses)

To install:

```
make && sudo make install
```

its that simple! (You need g++ compiler)

To uninstall:

```
sudo make clean
```

How to configure:

It is rather basic. You only change the respective values you want to change. Labels and ASCII lines are labelled via what order they will appear in.
Further information is provided in the header file itself!

#### Roadmap
  - ~~Display Window Manager~~
  - ~~Display Terminal~~
  - ~~Support for other POSIX compliant operating systems (BSDs)~~
  - Get working Desktop: variable for SunOS + FreeBSD
  - Some sembalance of configurability

#### Tested Distros and Operating Systems
  - Arch Linux
  - Manjaro Linux
  - Cainaima GNU/Linux
  - OpenIndiana
  - FreeBSD
