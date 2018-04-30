
Arduino Driver for SH1106 OLED Controller
=============================================
---

**Author**:   Noè Archimede Pezzoli (noearchimede@gmail.com)<br>
**Date**:  4/2018<br>

---

The SH1106 library provides useful functions to write text and images to a
display controlled by an SH1106 OLED driver storing as little data as possible
on the microcontroller (no buffer is required).

Currently this library only supports I2C interface, but other interfaces can be
easily added (only a little derived class needs to be implemented for every new
interface). Other display controllers may be made compatible as well.

The library is structured as follows:
1. User classes: *Label* and *Image*
2. SH1106 driver class: *SH1106_driver*
3. SH1106 interface classes: *SH1106_interfaces* -> *SH1106_I2C*, ...


---

The *Label* class provides the ability to write any ASCII character and some
other symbols in a proportional width font (as opposed to monospaced font),
quite small but well readable. The class automatically adds newlines to the
printed text taking care not to break words. Calling

`[Label::]print("Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis,");`

produces the following printed result:
```
Lorem ipsum dolor sit amet,
consectetuer adipiscing elit
Aenean commodo ligula eget
dolor. Aenean massa. Cum
sociis natoque penatibus et
magnis dis parturient
montes, nascetur ridiculus
mus. Donec quam felis,
```
It is possible to print text strings and literals stored either in RAM or in
Flash memory, integer and floating point numbers (optionally aligning numbers
on different lines), tabs, some control and other special characters, and any
custom symbol saved as plain arrays of bytes.

---

The *Image* class provides a simple interface to print bitmaps stored in byte
arrays. The arrays are print in the order showed in this example, were an image
of 5 pixels width and 4 pages height (5 x 32 pixels) is printed.
```
03-07-11-15-19 -> page 0 (1 page is 8 pixels high)
02-06-10-14-18 -> page 1
01-05-09-13-17 -> page 2
00-04-08-12-16 -> page 3
|  |  |  |  |  
v  v  v  v  v  
0  1  2  3  4 columns (each 1 pixel wide)
```
---

For more information please refer to the documentation in comments, wich can be
extracted with Doxygen and is available [here](http://htmlpreview.github.io/?https://github.com/noearchimede/SH1106/blob/master/Doc/html/index.html),
and to the example program.
