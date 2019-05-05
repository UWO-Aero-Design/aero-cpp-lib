1) Modify structs have _t specifiers 
2) Populate structs with proper values
3) Add comments to structs
4) Namespace structs
5) Comment ParsedMessage a bit more cause its confusing
6) Currently the buffer is a set 256 bytes so if you add to much data there could be a problem
    Either add a self checking assert/exception for when the sum of the size of the structs defined is greater than 256 or implement dynamic buffer length so uint_t* buf = new int
7) Dont have buffer segments in parsed message but pointers to structure elements
8) Test utility library
9) Add scaling factors for comm library so the protocol is defined already