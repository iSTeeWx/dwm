#! /bin/sh

if [[ $1 == "up" ]]; then
  brightnessctl set 10%+
else
  brightnessctl set 10%-
fi

current_brightness=$(brightnessctl | grep -Po '(?<=Current brightness: )\d+')
max_brightness=$(brightnessctl | grep -Po '(?<=Max brightness: )\d+')

echo $current_brightness
echo $max_brightness 

brightness=$(echo "scale=2; $current_brightness/$max_brightness*100" | bc)
brightness=$(echo $brightness/1 | bc)

HERBE_ID=/brightness-notification herbe "brightness: $brightness%"
