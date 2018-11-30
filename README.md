# ktot
Kepp Track of Time

## Building
clone this repo into some folder

```bash
git clone https://github.com/adrianoviana87/ktot.git ~/ktot
```
create a build directory
```bash
cd ~/ktot
mkdir build
```

run cmake and make
```bash
cd build
cmake ../ktot_app
make
```

now you can run the app in the build directory (for now)
```bash
./ktot --help
```