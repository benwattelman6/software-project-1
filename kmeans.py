import sys

POINTS_SEPARATOR = '\n'
COORDINATES_SEPARATOR = ','


def get_distance(p1, p2):
    assert len(p1) == len(p2)
    distance = 0
    for i in range(len(p1)):
        distance += (p1[i] - p2[i]) ** 2
    return distance


def get_points(filename):
    points = []
    with open(filename, 'r') as f:
        data = f.read()
    for point in data.split(POINTS_SEPARATOR):
        if len(point) != 0:
            points.append([float(n) for n in point.split(COORDINATES_SEPARATOR)])
    return points


def split_points_to_clusters(centroids, points):
    for c in centroids:
        c["sum"] = [0] * len(points[0])
        c["count"] = 0
    for point in points:
        min_cluster = 0
        min_distance = get_distance(point, centroids[0]["point"])
        for i in range(1, len(centroids)):
            distance = get_distance(point, centroids[i]["point"])
            if distance < min_distance:
                min_cluster, min_distance = i, distance
        centroids[min_cluster]["count"] += 1
        for j in range(len(point)):  # update sum of the point for the cluster
            centroids[min_cluster]["sum"][j] += point[j]


def calculate_new_centroids(centroids):
    """
    Updates the centroids and return if one of them has changed.
    """
    is_changed = False
    for i in range(len(centroids)):
        new_centroid = []
        for j in range(len(centroids[0]["point"])):
            new_centroid.append(centroids[i]["sum"][j] / centroids[i]["count"])  # calculate the average
            if new_centroid[j] != centroids[i]["point"][j]:
                is_changed = True
                centroids[i]["point"] = new_centroid
    return is_changed


def main():
    assert len(sys.argv) in [3, 4]
    k = int(sys.argv[1])
    filename = sys.argv[2]
    max_iter = int(sys.argv[3]) if len(sys.argv) > 3 else 200  # the default max_iter
    points = get_points(filename)
    centroids = []
    for i in range(k):  # initiate the centroids to be the first k points
        centroids.append({"point": points[i]})
    while max_iter > 0:
        split_points_to_clusters(centroids, points)
        if not calculate_new_centroids(centroids):  # there is no change in the centroids
            max_iter = 0  # breaks the loop
        max_iter -= 1
    output = POINTS_SEPARATOR.join([COORDINATES_SEPARATOR.join([str(round(i, 4)) for i in c["point"]]) for c in centroids])
    print(output)
    return output


if __name__ == '__main__':
    main()
