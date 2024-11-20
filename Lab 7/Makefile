JAVAC = javac

SRC_DIR = src

OUT_DIR = out

executor: src/executor/Simple_executor_test.java src/executor/CounterPlus.java src/executor/Counter.java
	$(JAVAC) -d $(OUT_DIR) $(SRC_DIR)/executor/*.java
	@java -cp $(OUT_DIR) $(SRC_DIR).executor.Simple_executor_test

zad_1: src/zad_1/Main.java src/zad_1/Calka.java
	$(JAVAC) -d $(OUT_DIR) $(SRC_DIR)/zad_1/*.java
	@java -cp $(OUT_DIR) $(SRC_DIR).zad_1.Main

zad_2: src/zad_2/Main.java src/zad_2/Calka_callable.java src/zad_1/Calka.java
	$(JAVAC) -d $(OUT_DIR) $(SRC_DIR)/zad_2/*.java
	@java -cp $(OUT_DIR) $(SRC_DIR).zad_2.Main

zad_3: src/zad_3/Main.java src/zad_3/DivideTask.java
	$(JAVAC) -d $(OUT_DIR) $(SRC_DIR)/zad_3/*.java
	@java -cp $(OUT_DIR) $(SRC_DIR).zad_3.Main

zad_4: src/zad_4/Main.java src/zad_4/Result.java src/zad_4/Calka_runnable.java
	$(JAVAC) -d $(OUT_DIR) $(SRC_DIR)/zad_4/*.java
	@java -cp $(OUT_DIR) $(SRC_DIR).zad_4.Main

zad_5: src/zad_5/Histogram_test.java src/zad_5/Obraz.java src/zad_5/Watek.java
	$(JAVAC) -d $(OUT_DIR) $(SRC_DIR)/zad_5/*.java
	@java -cp $(OUT_DIR) $(SRC_DIR).zad_5.Histogram_test

clean:
	rm -rf $(OUT_DIR)
