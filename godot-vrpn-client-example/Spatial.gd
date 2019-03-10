extends Spatial

var file
const vrpnClient = preload("res://bin/vrpnClient.gdns")
enum FINGERS {
		START
		ONE
		TWO
		THREE
		FOUR
		FIVE
		END
	}
var finger = FINGERS.START
var file_opened = false
var process_signal = false
var append = "hand"

var inst = null
func _ready():
	print(vrpnClient)
	inst = vrpnClient.new()
	inst.connect("Glove14Left@localhost")
	file = File.new()
	if file.open("res://data.txt", File.WRITE) != 0:
		print("Error opening file")
		file_opened = false
	else:
		file_opened = true
	read_fingers()

func _process(delta):
	if process_signal:
		inst.mainloop()
		#file.store_line(str(inst.analog))
		if(inst.analog.size() == 14):
			file.store_line(str(inst.analog[0]) + "," 
			+ str(inst.analog[1]) + "," 
			+ str(inst.analog[2]) + "," 
			+ str(inst.analog[3]) + "," 
			+ str(inst.analog[4]) + "," 
			+ str(inst.analog[5]) + "," 
			+ str(inst.analog[6]) + "," 
			+ str(inst.analog[7]) + "," 
			+ str(inst.analog[8]) + "," 
			+ str(inst.analog[9]) + "," 
			+ str(inst.analog[10]) + "," 
			+ str(inst.analog[11]) + "," 
			+ str(inst.analog[12]) + "," 
			+ str(inst.analog[13]) + "," 
			+ append)
		
func read_fingers():
	match finger:
		FINGERS.START:
			print("Starting...")
			$TimerStart.start()
			finger = FINGERS.ONE
		FINGERS.ONE:
			print("Starting with 1 finger")
			$TimerStart.start()
			finger = FINGERS.TWO
			append = "OneFinger"
		FINGERS.TWO:
			print("Starting with 2 finger")
			$TimerStart.start()
			finger = FINGERS.THREE
			append = "TwoFinger"
		FINGERS.THREE:
			print("Starting with 3 finger")
			$TimerStart.start()
			finger = FINGERS.FOUR
			append = "ThreeFinger"
		FINGERS.FOUR:
			print("Starting with 4 finger")
			$TimerStart.start()
			finger = FINGERS.FIVE
			append = "FourFinger"
		FINGERS.FIVE:
			print("Starting with 5 finger")
			$TimerStart.start()
			finger = FINGERS.ONE
			append = "FiveFinger"
		FINGERS.END:
			print("Ending...")
			append = "End"
			file.close()


func _on_TimerStart_timeout():
	print("Reading...")
	process_signal = true
	$TimerStop.start()

func _on_TimerStop_timeout():
	print("Stopping...")
	process_signal = false
	read_fingers()
