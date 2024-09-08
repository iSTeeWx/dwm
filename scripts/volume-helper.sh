#!/bin/bash

if [[ $1 == "up" ]]; then
	pactl set-sink-mute @DEFAULT_SINK@ false
	pactl set-sink-volume @DEFAULT_SINK@ +5%

	if [[ $(pactl get-sink-volume @DEFAULT_SINK@ | grep -Po '\d+(?=%)' | head -n 1) -ge 100 ]]; then
		pactl set-sink-volume @DEFAULT_SINK@ 100%
	fi

elif [[ $1 == "down" ]]; then
	pactl set-sink-volume @DEFAULT_SINK@ -5%

	if [[ $(pactl get-sink-volume @DEFAULT_SINK@ | grep -Po '\d+(?=%)' | head -n 1) -le 0 ]]; then
		pactl set-sink-mute @DEFAULT_SINK@ true
	else
		pactl set-sink-mute @DEFAULT_SINK@ false
	fi
elif [[ $1 == "mute" ]]; then
	pactl set-sink-mute @DEFAULT_SINK@ toggle
fi

sh /home/vlad/.local/src/dwmstatus/dwmstatus-restart
echo $(pactl get-sink-volume @DEFAULT_SINK@ | grep -Po '\d+(?=%)' | head -n 1)
echo $(pactl get-sink-mute @DEFAULT_SINK@)
