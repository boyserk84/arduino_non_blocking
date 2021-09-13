# Non-blocking Hardware Module scripts for Arduino

## Support hardware
* LED
* Buzzer
* OLED Display 

## How it works
* Each module script has `OnUpdate()` method.
* Inside the main Arudino project's loop, each module would call `OnUpdate()` method.
* Each module's script would then be executed every update call.

## Author
(Nate Kemavaha|[https://github.com/boyserk84]) 
