# ktot
Keep Track of Time

![screenshot](docs/ktot.gif "")

## Building
> Currently tested only on linux.
>
> Requires a c++ 17 compliant compiler

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