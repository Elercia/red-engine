function CopyFile(source, dest)
	cmd = os.translateCommands("{COPY} "..source.." "..dest.."")
	os.execute(cmd)
end