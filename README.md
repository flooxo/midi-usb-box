# midi-usb-box

### DIY MIDI Stompbox
This project is a DIY stompbox with 8 different knobs with each individual leds. The connection between Comupert and the box is done via USB. An Arduino Pro Micro is used, which has an ATmega32U4 chip and can therefore be recognized as a MIDI device. <br />
The bottom row of the leds is static and shows the current status of button (pressed -> on; not pressed -> off). The top row of leds can be addressed individually. For example, when the first key is pressed, it flashes to mimic a record key. In addition, buttons 3 and 4 are marked as pageUp/pageDown. This means that you can assign several actions to one button by turning the pages, so to speak.

### Usage
Due to its universal midi connection via USB, it can be used as normal midi device in any application. In my case I'm running it with FL Studio 20 to controll effects for my e-guitar.

### Compontents
 * Arduino Pro Micro (x1)
 * 3PDT footswitch (x8)
 * 5v LED Diode 5mm (x8)
 * Restistor (suitable for the led) (x8)
 * USB jack cable with mounting hole
 * cabels
 * alu case

### Pictures

![637844104465314966](https://user-images.githubusercontent.com/93255373/161239817-a22f2776-54da-45a6-b733-dc5721c037aa.png)
*front*

![637844104431340504](https://user-images.githubusercontent.com/93255373/161239829-ff3d6ac8-c2dd-4e9c-8155-f2ba8629a12c.png)
*back*

![637844104396629558](https://user-images.githubusercontent.com/93255373/161239795-3661ec4b-9236-45d0-b6a5-59279ebaddb5.png)
*inside*

### Circute Diagram
![SmartSelect_20220710-095550_Samsung Notes](https://user-images.githubusercontent.com/93255373/178136307-28f960a3-46dd-415c-aee6-435eb54c8961.jpg)

- - - -
###### all information without guarantee of correctness, is only my hobby on the side; for questions, suggestions or improvements please contact me
