import os
from rich.console import Console
from rich import print
from time import sleep

timefmt = "%Y-%m-%d %H:%M:%S"
console = Console(log_time=True, log_path=False, log_time_format=timefmt)
guess = "我是谁???"
filename = "image.txt"

def print_str_color(text, color):
	"""Prints text with ANSI color codes, centered within a box (if supported).

	Args:
		text (str): The text to print.
		color (str): The ANSI color code (e.g., "red", "blue").
		bgcolor (str, optional): The ANSI background color code. Defaults to None.
	"""
	text = text.upper()  # Convert to uppercase for consistent display
	term_width = 68
	padding = (term_width - 2 - len(text)) // 2
	remaining = (term_width - 2 - len(text)) % 2

	fmt = "=" * padding + f" [bold {color}]{text}[/bold {color}] " + "=" * (padding + remaining)
	console.print(fmt)

def get_abs_path(filename):
	"""Gets the absolute path of a file relative to the current executable."""
	dir_path = os.path.dirname(__file__)
	if dir_path is None:
		return None
	return os.path.join(dir_path, filename)

def print_image(pokemon_name, filename):
	"""Prints the text art from a file and the Pokemon name."""
	file_path = get_abs_path(filename)

	print_str_color(f"{guess}", "blue")

	if file_path is None:
		print(f"Error getting absolute path: {filename}")
		return -1

	try:
		with open(file_path, "r") as file:
			# Skip the first line (optional header)
			lines = file.readlines()

		for line in lines[1:]:
			print(line, end="")
			sleep(0.1)

	except FileNotFoundError:
		print(f"Error opening file: {file_path}")
		return -1

	print("")
	sleep(2)
	print_str_color(f"{pokemon_name}!", "cyan")

def print_desc_name(pokemon_name):
	"""Prints a motivational message before the description."""
	print("###")
	fmt = "### 在正式挑战" + f"[bold cyan]{pokemon_name}[/bold cyan]" + "之前，请仔细阅读并学习描述中的战斗技巧"
	console.print(fmt)
	print("### 如果感到吃力，请先尝试战胜其他低等级的宝可梦")
	print("### 祝你好运 :)")
	print("###")
	
def print_battle_result(name, color):
	print("\n### ", end="")
	fmt = "战斗记录:" + f" [bold {color}]{name}[/bold {color}] " + "获胜\n"
	console.log(fmt)
	print("### 努力提升自己的等级后，再来挑战吧！\n")

def get_pokemon_name(filename):
	filepath = get_abs_path(filename)

	with open(filepath, "r") as file:
		name = file.readline().strip()

	return name

def print_desc():
	global filename
	pokemon_name = get_pokemon_name(filename)
	print_image(pokemon_name, filename)
	print_desc_name(pokemon_name)

def print_exit():
	global filename
	pokemon_name = get_pokemon_name(filename)
	print_battle_result(pokemon_name, "red")
	
	