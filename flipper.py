import sensor, image, time, utime
from machine import UART

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time = 2000)
clock = time.clock()

red_count = 0
blue_count = 0
rectangle = [45,71,71,41]

uart = UART(3, 9600) # initialize uart bus
uart.init(9600, bits=8, parity=None, stop=1) # set parameters for uart communication

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.draw_rectangle(rectangle, color = (255, 0, 255))
    stats = img.get_statistics(roi=rectangle)
    red = stats.a_mean()
    blue = -stats.b_mean()

    #print(blue, red)

    if blue < 10:
        if red < 10:
            red_count += 1
        else:
            blue_count += 1

    if red_count > 50:
        print('flips')
        uart.write("1")
        red_count = 0
        blue_count = 0
        utime.sleep_ms(2000)
    elif blue_count > 50:
        print('slides')
        uart.write("0")
        red_count = 0
        blue_count = 0
        utime.sleep_ms(4000)

    else:
        print("no card")
        pass
