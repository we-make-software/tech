github:
	git add .
	git commit -m "Auto-commit from Makefile on $(shell date '+%Y-%m-%d %H:%M:%S')"
	git push origin main
