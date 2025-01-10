max_charge=$(cat /sys/class/power_supply/BAT0/charge_full_design)
current_charge=$(cat /sys/class/power_supply/BAT0/charge_now)
charge=$(echo "scale=2; $current_charge/$max_charge*100" | bc)
charge=$(echo $charge/1 | bc)
HERBE_ID=/battery-notification herbe "battery: $charge%"

