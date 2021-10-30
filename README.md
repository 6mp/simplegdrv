# simplegdrv

This is a simple interface for the gdrv.sys driver. In its current state this example just causes a Blue Screen of Death. <br>

# Usage

1. Load the gdrv.sys driver, testsigning does not need to be enabled since this is a signed driver
```
$ sc create gdrv binPath= path_to_gdrv.sys type= kernel
$ sc start gdrv
```

2. You can now use the example, I reccomend using some form of virtualization when experimenting with this.

# Credits
[SecureAuth](https://www.secureauth.com/labs/advisories/gigabyte-drivers-elevation-of-privilege-vulnerabilities/) 
