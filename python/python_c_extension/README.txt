for compiliation

the shared library (callback_manager.so)
gcc -fpic -shared -o libcallback_manager.so callback_manager.c

for the c executable (main_in_c)
gcc -L`pwd` -Wl,-rpath=`pwd` -Wall -o main_in_c main.c -lcallback_manager

for the python stuff
python3 setup.py install --prefix=`pwd`/install

... make sure the pythonpath and ld library path are set up accordingly
as python has no support for rpath


info found here
http://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
