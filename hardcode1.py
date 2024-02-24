import math

def calculate_aqi(pm25):
    """
    Calculate the Air Quality Index (AQI) based on PM2.5 concentration.
    """
    c = [(0, 12), (12.1, 35.4), (35.5, 55.4), (55.5, 150.4), (150.5, 250.4), (250.5, 350.4), (350.5, 500.4)]
    i = [(0, 50), (51, 100), (101, 150), (151, 200), (201, 300), (301, 400), (401, 500)]
    
    # Find the appropriate AQI range
    for index, (start, end) in enumerate(c):
        if start <= pm25 <= end:
            break
    
    # Calculate AQI
    aqi = ((i[index][1] - i[index][0]) / (c[index][1] - c[index][0])) * (pm25 - c[index][0]) + i[index][0]
    return round(aqi)

def calculate_aqi_category(aqi):
    """
    Determine the AQI category based on the AQI value.
    """
    if 0 <= aqi <= 50:
        return "Good"
    elif 51 <= aqi <= 100:
        return "Moderate"
    elif 101 <= aqi <= 150:
        return "Unhealthy for Sensitive Groups"
    elif 151 <= aqi <= 200:
        return "Unhealthy"
    elif 201 <= aqi <= 300:
        return "Very Unhealthy"
    elif 301 <= aqi <= 400:
        return "Hazardous"
    elif 401 <= aqi <= 500:
        return "Very Hazardous"
    else:
        return "Out of Range"

# Sample data from the provided JSON response
aqi_data = {
    "coord": {"lon": 77.0695, "lat": 28.7172},
    "main": {"aqi": 100}
}

# Extract PM2.5 concentration from the API response
pm25_concentration = aqi_data["main"]["aqi"]

# Calculate AQI based on PM2.5 concentration
aqi = calculate_aqi(pm25_concentration)

# Determine AQI category
aqi_category = calculate_aqi_category(aqi)

# Output results
print("Estimated PM2.5 level:", pm25_concentration)
print("Estimated AQI:", aqi)
print("AQI Category:", aqi_category)
