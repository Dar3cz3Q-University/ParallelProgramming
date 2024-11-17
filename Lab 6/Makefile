JAVAC = javac

SRC_DIR = src

OUT_DIR = out

variant_1:
	$(JAVAC) -d $(OUT_DIR) $(SRC_DIR)/variant_1/*.java
	@java -cp $(OUT_DIR) $(SRC_DIR).variant_1.Histogram_test

variant_2:
	$(JAVAC) -d $(OUT_DIR) $(SRC_DIR)/variant_2/*.java
	@java -cp $(OUT_DIR) $(SRC_DIR).variant_2.Histogram_test

variant_3:
	$(JAVAC) -d $(OUT_DIR) $(SRC_DIR)/variant_3/*.java
	@java -cp $(OUT_DIR) $(SRC_DIR).variant_3.Histogram_test

variant_4:
	$(JAVAC) -d $(OUT_DIR) $(SRC_DIR)/variant_4/*.java
	@java -cp $(OUT_DIR) $(SRC_DIR).variant_4.Histogram_test

variant_5:
	$(JAVAC) -d $(OUT_DIR) $(SRC_DIR)/variant_5/*.java
	@java -cp $(OUT_DIR) $(SRC_DIR).variant_5.Histogram_test

clean:
	rm -rf $(OUT_DIR)
