# Arduino-PPSKit
A library of boilerplate and examples for creating interworking clocks by people interested in keeping track of time.

This library attempts to distill the core time-keeping concepts presented in RFC1589, RFC2783, and RFC5905 standards into a set of simple classes, while discarding the NTP protocol and underlying tcp/ip stack the standards were meant to support.  If you are in need of a method to syncronize a clock to a reference clock without the burden of the internet, this library may be of help.

## Classes
### SystemClock() - A local, setable clock.
A local clock in hardware or software, wall time or not.
Because it is under our control, it can be nudged or reset at will.
  
### ReferenceClock() - An immutable, standard clock.
An immutable clock, typically remote, that can be queried for its time with an accuracy that we hope to apply to one of our own clocks.

An example of a reference clock might be the Cesium clock riding as payload in a GPS satellite.  To us it is immutable, we cant set it or influence it other than apply an offset to it.  To USNO, it is just one of many system clock under their maintenance and is queried and corrected on a schedule that fits their needs.

### PPSClock() - A clock with a pulse occuring on a seconds boundary.
An input that is aligned to the second boundary of some clock, reference or system.
  
### Statistics() - Mathematical comparison of two clocks
Creates and maintains the statistics between the accumulated timestamps of two related clocks.  Heavily used the by the discipline algorithm, and informational logging for understanding and judging clock quality.

### Discipline() - A clock calibration algorithm
Implements a frequency locked and phase locked loop for adjusting a local system clock to a reference clock.
  
### TimeVal() - A time instance container
A class to retain and manipulate an instant of time.

## PPSKit compatible Clocks to integrate with your projects:
  * DX-OSCHF-Clock
  * EmuRTC-System-Clock

## References
  * https://www.rfc-editor.org/info/rfc1589/
  * https://www.rfc-editor.org/info/rfc2783/
  * https://www.rfc-editor.org/info/rfc5905/
  
## Todo
  * pll wont lock. Get a stable pps before debugging. 
  
## Contibuting
This code is built by humans, for humans (despite what it may tell you, ai cares not one iota about time).  If you find a bug, misunderstanding, or enhancement you would like to address, I ask that you:

  * raise your right fleshy hand and truthfully say out loud 'I am a human.',
  * read and understand the W3C definition of generative AI found [here](https://www.w3.org/community/reports/ai-content-disclosure/CG-FINAL-ai-content-disclosure-20261009/#dfn-generative-ai) as it would apply to writing software,
  * and ensure your contribution does not violate the 'human-only' disclosure value defined [here](https://www.w3.org/community/reports/ai-content-disclosure/CG-FINAL-ai-content-disclosure-20261009/#disclosure-values).
  * If you make more than a minor change, add a copyright line with the year and your name above the previous contributor along with a terse description of the change.

## Notes
Many years ago I remember finding this modified Segal's Law as a signature in a long lost bbs post: "A man with one watch always knows what time it is, a man with two watches is never sure, but a man with three watches is someone who knows just how hard it is to tell time."
