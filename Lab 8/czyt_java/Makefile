JAVAC = javac

SRC_DIR = src

OUT_DIR = out

czytelnia:
	$(JAVAC) -d $(OUT_DIR) $(SRC_DIR)/*.java
	@java -cp $(OUT_DIR) Main

clean:
	rm -rf $(OUT_DIR)
