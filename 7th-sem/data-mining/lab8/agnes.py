import math
import random
import numpy as np
import matplotlib.pyplot as plt

class AgglomerativeHierarchicalClustering:
    def get_distance_measure(self):
        return lambda cluster_i, cluster_j: min([self.euclidean_distance(point_i, point_j) for point_i in cluster_i for point_j in cluster_j])
    
    def euclidean_distance(self, point_i, point_j):
        return math.sqrt(sum([(point_i[dim] - point_j[dim])**2 for dim in range(len(point_i))]))
    

    def __init__(self, data, K):
        self.data = data
        self.N = len(data)
        self.K = K
        self.measure = self.get_distance_measure()
        self.clusters = self.init_clusters()

    def init_clusters(self):
        return {data_id: [data_point] for data_id, data_point in enumerate(self.data)}

    def find_closest_clusters(self):
        min_dist = math.inf
        closest_clusters = None

        clusters_ids = list(self.clusters.keys())

        for i, cluster_i in enumerate(clusters_ids[:-1]):
            for j, cluster_j in enumerate(clusters_ids[i+1:]):
                dist = self.measure(self.clusters[cluster_i], self.clusters[cluster_j])
                if dist < min_dist:
                    min_dist, closest_clusters = dist, (cluster_i, cluster_j)
        return closest_clusters

    def merge_and_form_new_clusters(self, ci_id, cj_id):
        new_clusters = {0: self.clusters[ci_id] + self.clusters[cj_id]}

        for cluster_id in self.clusters.keys():
            if (cluster_id == ci_id) | (cluster_id == cj_id):
                continue
            new_clusters[len(new_clusters.keys())] = self.clusters[cluster_id]
        return new_clusters

    def plot_clusters_dynamic(self,clusterDataAtEachStep):
        #plot the clusters for each step
        for i,clusters in enumerate(clusterDataAtEachStep):
            plt.figure(i)
            for cluster_id, cluster in clusters.items():
                for point in cluster:
                    plt.scatter(point[0], point[1], color='C'+str(cluster_id))
            plt.show()
        


    def run_algorithm(self):
        clusterDataAtEachStep = []
        while len(self.clusters.keys()) > self.K:
            # self.print()
            clusterDataAtEachStep.append(self.clusters)
            closest_clusters = self.find_closest_clusters()
            self.clusters = self.merge_and_form_new_clusters(*closest_clusters)
        return clusterDataAtEachStep

    def print(self):
        for id, points in self.clusters.items():
            print("Cluster: {}".format(id))
            for point in points:
                print("    {}".format(point))

        
if __name__ == "__main__":
    # generate random data
    data = np.random.rand(10, 2)
    print(data)
    # run algorithm and print the dendrogram
    ahc = AgglomerativeHierarchicalClustering(data, 1)
    clusterDataAtEachStep = ahc.run_algorithm()
    ahc.plot_clusters_dynamic(clusterDataAtEachStep)
    # ahc.print()
