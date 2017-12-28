# ParamStorage
C++ experimental implementation and testing of parameter storage mechanism.
Say you got an embedded application with the need to store some of its parameters and data in an external EEPROM device and some 
other parameters in a Flash device. Wouldn't it be nice to have them defined as a complete global or local objects? much like a regular
variable that can be assigned and read from in runtime.
The implementation is done using C++ templates.
