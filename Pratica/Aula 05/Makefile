build: 
	pcompile $(filter-out $@,$(MAKECMDGOALS)).c
	ldpic32 $(filter-out $@,$(MAKECMDGOALS)).hex
	@echo
	rm $(filter-out $@,$(MAKECMDGOALS)).map
	rm $(filter-out $@,$(MAKECMDGOALS)).elf
	rm $(filter-out $@,$(MAKECMDGOALS)).o
	pterm


