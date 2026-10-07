import { Transaction } from './transaction.model';

export interface QuickAction {
  label: string;
  icon: string;
  route: string;
}

export interface DashboardData {
  userName: string;
  greeting: string;
  initials: string;
  balance: number;
  accountNumber: string;
  trend: number;
  actions: QuickAction[];
  transactions: Transaction[];
}
