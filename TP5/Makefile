CC = clang
CFLAGS = -Wall

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

TARGETS = $(addprefix $(BIN_DIR)/, test_terrain test_robot robot_terrain)

all: $(TARGETS)


$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/test_terrain.o: $(SRC_DIR)/terrain.h

$(BUILD_DIR)/test_robot.o: $(SRC_DIR)/robot.h

$(BUILD_DIR)/robot_terrain.o: $(SRC_DIR)/terrain.h $(SRC_DIR)/robot.h


$(BIN_DIR)/test_terrain: $(BUILD_DIR)/test_terrain.o $(BUILD_DIR)/terrain.o | $(BIN_DIR)
	$(CC) $^ -o $@

$(BIN_DIR)/test_robot: $(BUILD_DIR)/test_robot.o $(BUILD_DIR)/robot.o | $(BIN_DIR)
	$(CC) $^ -o $@

$(BIN_DIR)/robot_terrain: $(BUILD_DIR)/robot_terrain.o $(BUILD_DIR)/terrain.o $(BUILD_DIR)/robot.o | $(BIN_DIR)
	$(CC) $^ -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
