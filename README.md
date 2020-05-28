# ifbind
Bind two network interfaces to simulate al loop back.

This program was created as an alternative to bind two L2TP network inerfaces. Using `brctl` didn't work.

## Build
```bash
sudo make apt-deps
make build
sudo make install
```
## Usage

### Help
To print the help for the arguments: `./ifbind --help`

### Simple bind
```bash
sudo ./ifbind --bridge tunnel1:tunnel2 --bridge tunnel3:tunnel4
```

### Debug
To activate the debug level and view each packets being forwarded:
use the `--debug` (or `-D`) argument.

```bash
sudo ./ifbind --debug --bridge tunnel1:tunnel2
```

### Interactive Mode
To use the interactive mode use the argument `--interactive` (or `-I`).

The interactive mode allow you to connect/disconnect binded interfaces by providing a CLI.  
Nothe that the logs are outputed in the fine `ifbind.log` located in `pwd`.

To view a list of commands, in the CLI type `help`.
