#!/bin/bash

old_volume=$(pactl get-sink-volume 0)
old_mute=$(pactl get-sink-mute 0)

if [[ $1 == "up" ]]; then
	pactl set-sink-mute 0 false
	pactl set-sink-volume 0 +5%

	if [[ $(pactl get-sink-volume 0 | grep -Po '\d+(?=%)' | head -n 1) -ge 100 ]]; then
		pactl set-sink-volume 0 100%
	fi

elif [[ $1 == "down" ]]; then
	pactl set-sink-volume 0 -5%

	if [[ $(pactl get-sink-volume 0 | grep -Po '\d+(?=%)' | head -n 1) -le 0 ]]; then
		pactl set-sink-mute 0 true
	else
		pactl set-sink-mute 0 false
	fi

elif [[ $1 == "mute" ]]; then
	pactl set-sink-mute 0 toggle
fi

if [[ $old_volume != $(pactl get-sink-volume 0) || $old_mute != $(pactl get-sink-mute 0) ]]; then
	if [[ $(pactl get-sink-mute 0) == "Mute: yes" ]]; then
		HERBE_ID=/volume-notification herbe "volume: mute"
	else
		HERBE_ID=/volume-notification herbe "volume: $(pactl get-sink-volume 0 | grep -Po '\d+(?=%)' | head -n 1)%"
	fi
fi
