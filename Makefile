TARGET ?= knapsack_sa
CFLAGS = -Wall -Wextra
LINKS = -lm

$(TARGET): $(TARGET).c
	gcc $(CFLAGS) $(TARGET).c -o $(TARGET) $(LINKS)
clean:
	rm -f $(TARGET)
