# c - cpp Randomizer
Thank you for your interest in my project :)
### Why this project?
I am a cheat developer, I work on things like reverse engineering. I offer a good service with very advanced systems. I noticed that Anti-Cheats can detect some properties like ProjectGuid, void names, SolutionGuid. As I said, I already have advanced systems, and I use the auto build system for the products. With this project, they can stay undetected more.

# New Features!
 - Vcxproject Solution Guid Randomizer
 - Solution File Guid Randomizer
 - Randomize Defined section
 - Supporting sub folders.
 
### How can i use?
**In project;**
- In this [line](https://github.com/SwenenzY/cpp-c-randomizer/blob/main/Source/main.cpp#L78) you can edit file path, make sure it ends with \\\\ at the end. Also you can see settings in file you can change settings. 

**In your code;**
- Define 2 type start - end
- Type 1 = Searching in all files
- Type 2 = Search only in own files (varriable-voids-etc.)
 ```cpp
#define O_O // type 1
#define o_o // type 1
#define O__O // type 2
#define o__o // type 2
std::string O_O MyUniqueString o_o = "";
             ^                  ^
             |                  |
             Start              End
 // Program can detect multiple defines in 1 line 
 // Make sure that variables have a unique name. The program may make mistakes.
```
 ### **Example Input;**
  ```cpp
  void O_O TestVoid1 o_o (int O_O TestInt1 o_o, std::string O_O TestString1 o_o);

namespace O_O TestNamespace o_o {
	bool O_O TestNamespaceVoid1 o_o (bool O_O TestBool1 o_o);
}

class O_O TestClass o_o {
public:
	static float O_O MyClassVoid1 o_o (float O_O MyFlaot1 o_o = 3.f);
	static void  O_O MyClassVoid2 o_o (float O_O MyFloat2 o_o);
	static void  O_O MyClassVoid3 o_o ();
private:
	static void O_O MyclassVoid4 o_o ();
};
  ```
 ### **Example Output;**
  ```cpp
 void O_O eLlV8UWrXhDSvwO o_o (int O_O sckFeJWHdXVBQn4 o_o, std::string O_O vmVb12AbaTKduWp o_o);

namespace O_O qAPSKmAl19bgenC o_o {
	bool O_O EFaVYTc50PL1I2j o_o (bool O_O MutG7cf592wTOYb o_o);
}

class O_O uKyJlAqFoFnq0dg o_o {
public:
	static float O_O IXRXXX8zSkTBS50 o_o (float O_O rbsii5szSNIeJ4A o_o = 3.f);
	static void  O_O dyKqlzoiLN9mONI o_o (float O_O vXHO04fW4i7BOZa o_o);
	static void  O_O alFAq67MIGDan6y o_o ();
private:
	static void O_O UiMpuVI4jWlI6Zo o_o ();
};
  ```
Example [image](https://imgur.com/sSsvZwT)

Example [image2](https://imgur.com/HGj1QcR)
### Tech
If you have suggestion and you error please notify me in [issues](https://github.com/SwenenzY/cpp-c-randomizer/issues).
- Visual Studio 2015+
- /clr Support (C/C++ CLI)

License
----

MIT

**[Fun4Cheats.com](https://Fun4Cheats.com)**

**[Mail Me!](mailto:mail@swenenzy.com)**
