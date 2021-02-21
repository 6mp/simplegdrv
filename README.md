# simplegdrv

This is a simple interface for the gdrv.sys driver. In its current state this example just causes a Blue Screen of Death. <br>

# Usage

1. Load the gdrv.sys driver, testsigning does not need to be enabled since this is a signed driver
```
$ sc create gdrv binPath= path_to_gdrv.sys type= kernel
$ sc start gdrv
```

2. You can now use the example, I reccomend using some form of virtualization when experimenting with this.

# Purpose

I made this driver interface to learn more about the process in which one communicates with a driver and how this can be a security vulenrability. <br>
This ties in with my [simpledriver](https://github.com/unmap/simpledriver) which also uses IOCTL communcation since I was able to the internals and development of a similar driver.
# In the future

Moving on from this I will be researching more on how a driver using IOCTL communication could be protected from unauthorized access.

# Credits

[SecureAuth](https://www.secureauth.com/labs/advisories/gigabyte-drivers-elevation-of-privilege-vulnerabilities/) 
