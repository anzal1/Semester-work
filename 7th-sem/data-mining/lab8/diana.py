import numpy as np
import matplotlib.pyplot as plt
import random 
def euclidean_distance(a, b):
    return np.linalg.norm(a - b)

def compute_centroid(points):
    return np.mean(points, axis=0)


def generate_k_different_colors(k):
    colors = []
    for i in range(k):
        colors.append('#%06X' % random.randint(0, 0xFFFFFF))
    return colors





def diana_clustering(points, k):
    #all points should be in one cluster
    clusters = [points]
    step = 0
    colors=generate_k_different_colors(k)
    #store clusters with priority as the number of points in the cluster
    #now we need to split the clusters
    while len(clusters) <= k:
        #choose a cluster to split
        plt.title("Step: "+str(step+1))
        #show cluster id , color and number of points in the cluster
        for cluster_id, cluster in enumerate(clusters):
            plt.text(cluster[0][0], cluster[0][1], str(cluster_id)+" "+str(len(cluster)), color=colors[cluster_id])
        for cluster_id, cluster in enumerate(clusters):
            for point in cluster:
                #give unique color to each cluster use c
                plt.scatter(point[0], point[1], color=colors[cluster_id])
        plt.show()
        step += 1
        cluster_to_split = max(clusters, key=len)
        print("cluster to split: ", cluster_to_split)
        #find the two points that are furthest apart
        max_dist = 0
        for i in range(len(cluster_to_split)):
            for j in range(i+1, len(cluster_to_split)):
                dist = euclidean_distance(cluster_to_split[i], cluster_to_split[j])
                if dist > max_dist:
                    max_dist = dist
                    split_point_1 = cluster_to_split[i]
                    split_point_2 = cluster_to_split[j]
        #now we have the two points that are furthest apart
        #we need to split the cluster into two clusters
        new_cluster_1 = []
        new_cluster_2 = []
        for point in cluster_to_split:
            dist_1 = euclidean_distance(point, split_point_1)
            dist_2 = euclidean_distance(point, split_point_2)
            if dist_1 < dist_2:
                new_cluster_1.append(point)
            else:
                new_cluster_2.append(point)
        #remove the old cluster and add the two new clusters
        # check if the cluster_to_split is in the clusters list
        clusters.remove(cluster_to_split)
        clusters.append(new_cluster_1)
        clusters.append(new_cluster_2)
        #plot the clusters
        


    return clusters





# Generate 15 random points
np.random.seed(0)
points = np.random.rand(15, 2)

# Perform Diana clustering with k=3

clusters = diana_clustering(points, len(points))
# Plot the points and clusters at each step

