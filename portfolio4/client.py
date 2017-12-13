#Base Python client for MEng in IoT Assignment
#consumes data from IoT Gateway
import urllib.request
import matplotlib.pyplot as plt

def find_Value(phare_value,find_value):
    start = phare_value.find('<' + find_value +'>') + len(find_value) + 2
    end = phare_value.find('</' + find_value +'>')
    return phare_value[start:end];

response = urllib.request.urlopen('http://localhost:8080/')
resp = response.read()
data_str = str(resp)
data_line = data_str.split("\\n")
i = 1
time_reading = []
temperature_reading = []
for line in data_line:
    if i < len(data_line):
        time_reading.append(find_Value(phare_value = data_line[i],find_value = 'time'))
        temperature_reading.append(find_Value(phare_value = data_line[i],find_value = 'temperature'))
        i = i+1

plt.figure(1)
plt.plot(time_reading, temperature_reading, 'k')
plt.show()
