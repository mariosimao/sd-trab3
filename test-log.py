# Adapted from https://www.cos.ufrj.br/~daniel/sd/trabalhos/log_validator.py

def validate():
    f = open("message.log", "r")
    lines = f.readlines()
    requests = []
    grants = []
    releases = []

    for line in lines:
        if ("REQUEST" in line):
            requests.append(int(line.split("\t")[2]))
            continue
        if ("GRANT" in line):
            if (len(grants) != len(releases)):
                print(line)
                print(len(grants))
                print(len(releases))
                raise Exception("Invalid log file: invalid grants and releases sequence")
            grants.append(int(line.split("\t")[2]))
            continue
        if ("RELEASE" in line):
            if (len(releases) != len(grants) - 1):
                print(line)
                raise Exception("Invalid log file: invalid grants and releases sequence")
            releases.append(int(line.split("\t")[2]))
            continue

    # for i in range(len(requests)):
    #     if (requests[i] != grants[i] or grants[i] != releases[i]):
    #         raise Exception("Invalid log file: invalid grants and releases sequence")

    print("Log file was successfully validated")

if __name__ == "__main__":
    validate()
