print("Hello Cica!")
pin=7
gpio.mode(pin, gpio.OUTPUT)
--gpio.write(2, gpio.HIGH)
gpio.write(pin, gpio.LOW)

lighton=0
tmr.alarm(0,1000,1,function()
if lighton==0 then 
    lighton=1 
    gpio.write(pin, gpio.LOW)
    -- 512/1024, 50% duty cycle
else 
    lighton=0 
    gpio.write(pin, gpio.HIGH)
end 
end)